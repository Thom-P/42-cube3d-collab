/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:18:14 by tplanes           #+#    #+#             */
/*   Updated: 2023/01/13 16:43:46 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_prep_nbr(char **out, long int nbr, char *sign, t_tags *tags);

static int	ft_is_sign_cat(char **out, char *sign, int *nbr_len, t_tags *tags);

static int	ft_print_int_sub(long int nbr, t_tags *tags, int *nb_chr_prt);

/* Handle both int and uint input */
int	ft_print_int(va_list ap, t_tags *tags, int *nb_chr_prt)
{
	long int	nbr;

	if (tags -> spec == 'u')
		nbr = (long int)va_arg(ap, unsigned int);
	else
		nbr = (long int)va_arg(ap, int);
	if (ft_print_int_sub(nbr, tags, nb_chr_prt))
		return (-1);
	return (0);
}

/* Format number with optional tags and print it*/
static int	ft_print_int_sub(long int nbr, t_tags *tags, int *nb_chr_prt)
{
	char		*out;
	int			nbr_len;
	char		sign;			
	int			is_sign_cat;

	if (ft_prep_nbr(&out, nbr, &sign, tags))
		return (-1);
	if (nbr == 0 && tags -> prec == 0)
		out[0] = '\0';
	nbr_len = ft_strlen(out);
	if (ft_format_prec(&out, &nbr_len, tags))
		return (-1);
	is_sign_cat = ft_is_sign_cat(&out, &sign, &nbr_len, tags);
	if (is_sign_cat == -1 || ft_format_width(&out, &nbr_len, tags))
		return (-1);
	if (!is_sign_cat && sign != 0)
		out[0] = sign;
	if (write(tags -> fd, out, nbr_len) == -1)
	{
		free(out);
		return (-1);
	}
	(*nb_chr_prt) += nbr_len;
	free(out);
	return (0);
}

/* Fetch sign and returns char* of unsigned number */
static int	ft_prep_nbr(char **out, long int nbr, char *sign, t_tags *tags)
{
	char	*str;

	*sign = 0;
	if (nbr < 0)
	{
		*sign = '-';
		nbr = -nbr;
	}
	else if (tags -> flag_str[1] == '+')
		*sign = '+';
	else if (tags -> flag_str[2] == ' ')
		*sign = ' ';
	str = ft_litoa(nbr);
	if (str == NULL)
		return (-1);
	*out = str;
	return (0);
}

/* Attach sign if nbr not left justified and no leading zeroes */
static int	ft_is_sign_cat(char **out, char *sign, int *nbr_len, t_tags *tags)
{		
	char	*str;
	int		is_not_left_just;
	int		is_lead_zero;

	is_not_left_just = tags -> flag_str[0] == '_';
	is_lead_zero = (tags -> flag_str[4] == '0' && tags -> width > *nbr_len + 1);
	if (*sign == 0 || (is_not_left_just && is_lead_zero))
		return (0);
	str = ft_strjoin("_", *out);
	free(*out);
	if (str == NULL)
		return (-1);
	str[0] = *sign;
	*out = str;
	(*nbr_len)++;
	return (1);
}
