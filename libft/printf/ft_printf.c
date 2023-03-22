/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:25:49 by tplanes           #+#    #+#             */
/*   Updated: 2023/01/13 16:43:13 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_init_tags(int fd, t_tags *tags);

static int	ft_parse(const char **p_fmt, t_tags *tags);

static int	ft_print(va_list ap, t_tags *tags, int *nb_chr_prt);

static int	ft_is_print_char(int fd, const char **p_fmt, int *nb_chr_prt);

/* CURRENTLY SUPPORTED OPTIONS:
flags: "-+ #0", specifiers: "cdisuxXp%"
flag_str contains flag chars at corresp. position if parsed, or defaut to '_'
Eg: flag_str = "_+__0" 
width (int): min # of chars to be printed
precision (int): min # of digits to be printed
spec (char): specifier */
int	ft_printf(int fd, const char *fmt, ...)
{
	va_list	ap;
	t_tags	tags;
	int		nb_chr_prt;
	int		is_print;	

	va_start(ap, fmt);
	nb_chr_prt = 0;
	while (*fmt)
	{
		is_print = ft_is_print_char(fd, &fmt, &nb_chr_prt);
		if (is_print == 1)
			continue ;
		else if (is_print == -1)
			break ;
		ft_init_tags(fd, &tags);
		if (ft_parse(&fmt, &tags) || ft_print(ap, &tags, &nb_chr_prt))
		{
			va_end(ap);
			return (-1);
		}
	}
	va_end(ap);
	return (nb_chr_prt);
}

/* Just print current char if no % detected */
static int	ft_is_print_char(int fd, const char **p_fmt, int *nb_chr_prt)
{
	if (**p_fmt != '%')
	{
		if (write(fd, *p_fmt, 1) == -1)
		{	
			*nb_chr_prt = -1;
			return (-1);
		}
		(*p_fmt)++;
		(*nb_chr_prt)++;
		return (1);
	}
	(*p_fmt)++;
	return (0);
}

/* Tags initialization: flag_str initialized at "_____\0" */
static int	ft_init_tags(int fd, t_tags *tags)
{
	ft_memset(tags -> flag_str, '_', 5);
	ft_bzero(tags -> flag_str + 5, 1);
	tags -> width = -1;
	tags -> prec = -1;
	tags -> spec = '\0';
	tags -> fd = fd;
	return (0);
}

/* Parsing */
static int	ft_parse(const char **p_fmt, t_tags *tags)
{
	if (ft_parse_flags(p_fmt, tags))
		return (-1);
	if (ft_parse_width(p_fmt, tags))
		return (-1);
	if (ft_parse_prec(p_fmt, tags))
		return (-1);
	if (ft_parse_spec(p_fmt, tags))
		return (-1);
	ft_check_tag_consistency(tags);
	return (0);
}

/* Specifier set: "cdisuxXp%"
Used function pointer array to handle each specifier */
static int	ft_print(va_list ap, t_tags *tags, int *nb_chr_prt)
{
	char	*spec_set;
	int		(*f_ptr[9])(va_list ap, t_tags *tags, int *nb_chr_prt);
	int		ind_spec;

	spec_set = "cdisuxXp%";
	f_ptr[0] = ft_print_str_char;
	f_ptr[1] = ft_print_int;
	f_ptr[2] = ft_print_int;
	f_ptr[3] = ft_print_str_char;
	f_ptr[4] = ft_print_int;
	f_ptr[5] = ft_print_hex;
	f_ptr[6] = ft_print_hex;
	f_ptr[7] = ft_print_hex;
	f_ptr[8] = ft_print_str_char;
	ind_spec = ft_ind_in_set(tags -> spec, spec_set);
	if (f_ptr[ind_spec](ap, tags, nb_chr_prt))
		return (-1);
	return (0);
}
