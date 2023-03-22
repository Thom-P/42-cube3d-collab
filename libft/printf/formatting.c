/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 17:02:33 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/02 12:26:59 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//Add leading zeroes to so that total # of chars = prec
int	ft_format_prec(char **out, int *nbr_len, t_tags *tags)
{
	char	*str;
	int		prec;
	int		ind_start_cpy;

	prec = tags -> prec;
	if (prec <= *nbr_len)
		return (0);
	str = (char *)malloc(prec + 1);
	if (str == NULL)
	{
		free(*out);
		return (-1);
	}
	ft_memset(str, '0', prec - *nbr_len);
	str[prec] = '\0';
	ind_start_cpy = prec - *nbr_len;
	ft_memcpy(str + ind_start_cpy, *out, *nbr_len);
	free(*out);
	*out = str;
	*nbr_len = prec;
	return (0);
}

//Add leading ' ' or '0', or trailing ' ' so that total # of chars = width
int	ft_format_width(char **out, int *str_len, t_tags *tags)
{	
	char	pad;
	char	*str;
	int		ind_start_cpy;

	if (tags -> width <= *str_len)
		return (0);
	pad = ' ';
	if (tags -> flag_str[4] == '0')
		pad = '0';
	str = (char *)malloc(tags -> width + 1);
	if (str == NULL)
	{
		free(*out);
		return (-1);
	}
	ft_memset(str, pad, tags -> width);
	str[tags -> width] = '\0';
	ind_start_cpy = 0;
	if (tags -> flag_str[0] != '-')
		ind_start_cpy = tags -> width - *str_len;
	ft_memcpy(str + ind_start_cpy, *out, *str_len);
	free(*out);
	*out = str;
	*str_len = tags -> width;
	return (0);
}

/* Precision and left justify both overide leading 0 flag
Flag '+' and ' ' only valid for d, i, and u specifiers 
Flag '0' invalid if specifier p */
void	ft_check_tag_consistency(t_tags *tags)
{
	int	is_lead_zer;

	is_lead_zer = (tags -> flag_str[4] == '0');
	if (is_lead_zer && (tags -> prec != -1 || tags -> flag_str[0] == '-'))
		tags -> flag_str[4] = '_';
	if (tags -> spec == 'p' && is_lead_zer)
		tags -> flag_str[4] = '_';
	if (tags -> spec != 'd' && tags -> spec != 'i' && tags -> spec != 'u')
	{
		tags -> flag_str[1] = '_';
		tags -> flag_str[2] = '_';
	}
	return ;
}

// Returns index of char c in set, or -1 if not found
int	ft_ind_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (i);
		i++;
	}
	return (-1);
}
