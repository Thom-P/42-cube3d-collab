/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:34:52 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/20 12:35:55 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c);

int	ft_atoi(const char *str)
{
	int	flag_sign;
	int	res;

	flag_sign = 1;
	res = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{	
		flag_sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - '0');
	return (res * flag_sign);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
