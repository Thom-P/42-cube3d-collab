/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:45:24 by tplanes           #+#    #+#             */
/*   Updated: 2023/01/13 16:41:39 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

//t_tags holds all tags (flags, width, precision, specifier)
typedef struct s_tags
{
	char		flag_str[6];
	int			width;
	int			prec;
	char		spec;
	int			fd;
}				t_tags;

typedef unsigned long	t_ulong;

// Project
int		ft_printf(int fd, const char *format, ...);

// Parsing
int		ft_parse_flags(const char **p_fmt, t_tags *tags);
int		ft_parse_width(const char **p_fmt, t_tags *tags);
int		ft_parse_prec(const char **p_fmt, t_tags *tags);
int		ft_parse_spec(const char **p_fmt, t_tags *tags);

// Printing
int		ft_print_str_char(va_list ap, t_tags *tags, int *nb_chr);
int		ft_print_int(va_list ap, t_tags *tags, int *nb_chr);
int		ft_print_hex(va_list ap, t_tags *tags, int *nb_chr);

// Formatting
int		ft_format_prec(char **out, int *str_len, t_tags *tags);
int		ft_format_width(char **out, int *str_len, t_tags *tags);

// Extra
void	ft_check_tag_consistency(t_tags *tags);
int		ft_ind_in_set(char c, char *set);
char	*ft_ultoa_base(t_ulong n, char *base);
char	*ft_litoa(long int n);	

#endif
