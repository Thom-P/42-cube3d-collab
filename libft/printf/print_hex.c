/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:18:14 by tplanes           #+#    #+#             */
/*   Updated: 2023/01/13 16:44:35 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_sub(t_ulong nbr, t_tags *tags, int *nb_chr_prt, int is_ptr);

static int	ft_join_pfix(char **out, int *is_pfix, int *nbr_len, t_tags *tags);

static void	ft_wr_pfix_caps(char **out, int is_pfix, t_ulong nbr, t_tags *tags);

static void	ft_toupper_str(char *str);

/* Handle x, X, and p cases */
int	ft_print_hex(va_list ap, t_tags *tags, int *nb_chr_prt)
{
	unsigned long	nbr;
	int				is_ptr;

	is_ptr = 0;
	if (tags -> spec == 'p')
	{
		is_ptr = 1;
		nbr = va_arg(ap, unsigned long);
	}
	else
		nbr = (unsigned long)va_arg(ap, unsigned int);
	if (ft_hex_sub(nbr, tags, nb_chr_prt, is_ptr))
		return (-1);
	return (0);
}

/* Convert nbr to hex base char* and format according to tags, then print */
static int	ft_hex_sub(t_ulong nbr, t_tags *tags, int *nb_chr_prt, int is_ptr)
{
	char	*out;
	int		nbr_len;
	int		is_pfix;

	out = ft_ultoa_base(nbr, "0123456789abcdef");
	if (out == NULL)
		return (-1);
	if (nbr == 0 && tags -> prec == 0)
		out[0] = '\0';
	nbr_len = ft_strlen(out);
	if (ft_format_prec(&out, &nbr_len, tags))
		return (-1);
	if ((nbr > 0 || is_ptr) && ft_join_pfix(&out, &is_pfix, &nbr_len, tags))
		return (-1);
	if (ft_format_width(&out, &nbr_len, tags))
		return (-1);
	ft_wr_pfix_caps(&out, is_pfix, nbr, tags);
	if (write(tags -> fd, out, nbr_len) == -1)
	{
		free(out);
		return (-1);
	}
	(*nb_chr_prt) += nbr_len;
	free(out);
	return (0);
}

/*  Join 0x prefix to number if no leading 0 and # flag (or specifier p) */
static int	ft_join_pfix(char **out, int *is_pfix, int *nbr_len, t_tags *tags)
{
	char	*tmp;
	int		is_lead_zero;

	*is_pfix = 0;
	is_lead_zero = (tags -> flag_str[4] == '0' && tags -> width > *nbr_len + 2);
	if (tags -> spec != 'p' && (tags -> flag_str[3] != '#' || is_lead_zero))
		return (0);
	tmp = *out;
	*out = ft_strjoin("0x", tmp);
	free(tmp);
	if (*out == NULL)
		return (-1);
	*is_pfix = 1;
	*nbr_len = ft_strlen(*out);
	return (0);
}

/* Write 0x prefix if not attached before, and put upper case if specifier X*/
static void	ft_wr_pfix_caps(char **out, int is_pfix, t_ulong nbr, t_tags *tags)
{
	if (!is_pfix && nbr > 0 && tags -> flag_str[3] == '#')
	{
		(*out)[0] = '0';
		(*out)[1] = 'x';
	}
	if (tags -> spec == 'X')
		ft_toupper_str(*out);
	return ;
}

/* Change str to upper caps */
static void	ft_toupper_str(char *str)
{
	while (*str)
	{	
		*str = (char)ft_toupper(*str);
		str++;
	}
	return ;
}
