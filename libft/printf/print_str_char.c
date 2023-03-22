/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:05:30 by tplanes           #+#    #+#             */
/*   Updated: 2023/01/13 16:44:09 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_str_sub(char *out, t_tags *tags, int *nb_chr_prt);

/* Handle both str or char input
out is duplicated from va_arg so it can always be freed within print_str_sub */
int	ft_print_str_char(va_list ap, t_tags *tags, int *nb_chr_prt)
{	
	char	*in_str;
	char	*out;

	if (tags -> spec == 's')
	{	
		in_str = va_arg(ap, char *);
		if (in_str == NULL)
			in_str = "(null)";
		out = ft_strdup(in_str);
		if (out == NULL)
			return (-1);
	}
	else
	{
		out = (char *)malloc(1 + 1);
		if (out == NULL)
			return (-1);
		out[0] = '%';
		if (tags -> spec != '%')
			out[0] = (char)va_arg(ap, int);
		out[1] = '\0';
	}
	if (ft_print_str_sub(out, tags, nb_chr_prt))
		return (-1);
	return (0);
}

/* Formats and print str or char 
Need to force strlen to 1 in case of char to print possible char '\0' */
static int	ft_print_str_sub(char *out, t_tags *tags, int *nb_chr_prt)
{
	int	str_len;
	int	is_str;

	str_len = 1;
	is_str = (tags -> spec == 's');
	if (is_str)
		str_len = (int)ft_strlen(out);
	if (is_str && tags -> prec >= 0 && tags -> prec < str_len)
	{
		str_len = tags -> prec;
		out[str_len] = '\0';
	}
	if (ft_format_width(&out, &str_len, tags))
		return (-1);
	if (write(tags -> fd, out, str_len) == -1)
	{
		free(out);
		return (-1);
	}
	(*nb_chr_prt) += str_len;
	free(out);
	return (0);
}
