/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 08:22:57 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/02 13:01:18 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_flags(const char **p_fmt, t_tags *tags)
{
	char	*flag_set;
	int		ind;

	flag_set = "-+ #0";
	while (**p_fmt != 0)
	{
		ind = ft_ind_in_set(**p_fmt, flag_set);
		if (ind == -1)
			return (0);
		tags -> flag_str[ind] = flag_set[ind];
		(*p_fmt)++;
	}	
	return (-1);
}

int	ft_parse_width(const char **p_fmt, t_tags *tags)
{
	if (!ft_isdigit(**p_fmt))
		return (0);
	tags -> width = ft_atoi(*p_fmt);
	while (ft_isdigit(**p_fmt))
		(*p_fmt)++;
	if (**p_fmt == 0)
		return (-1);
	return (0);
}

int	ft_parse_prec(const char **p_fmt, t_tags *tags)
{
	if (**p_fmt != '.')
		return (0);
	tags -> prec = 0;
	(*p_fmt)++;
	if (**p_fmt == 0)
		return (-1);
	if (!ft_isdigit(**p_fmt))
		return (0);
	tags -> prec = ft_atoi(*p_fmt);
	while (ft_isdigit(**p_fmt))
		(*p_fmt)++;
	if (**p_fmt == 0)
		return (-1);
	return (0);
}

int	ft_parse_spec(const char **p_fmt, t_tags *tags)
{
	char	*spec_set;
	int		ind;

	spec_set = "cdisuxXp%";
	ind = ft_ind_in_set(**p_fmt, spec_set);
	if (ind == -1)
		return (-1);
	tags -> spec = **p_fmt;
	(*p_fmt)++;
	return (0);
}
