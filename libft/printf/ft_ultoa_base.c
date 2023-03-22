/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:21:30 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/02 12:29:53 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_recur_write(char **ptr_res, t_ulong n, int nb_dig, char *base);

/* Converts unsigned long to char* */
char	*ft_ultoa_base(t_ulong n, char *base)
{
	char	*res;

	if (ft_recur_write(&res, n, 1, base) == 0)
		return (NULL);
	return (res);
}

static int	ft_recur_write(char **ptr_res, t_ulong n, int nb_dig, char *base)
/* Returns index of next digit to write */
{
	int				i_dig;
	unsigned long	base_len;

	base_len = ft_strlen(base);
	if (n <= base_len - 1)
	{
		*ptr_res = (char *)malloc(nb_dig + 1);
		if (*ptr_res == NULL)
			return (0);
		(*ptr_res)[0] = base[n];
		(*ptr_res)[nb_dig] = '\0';
		return (1);
	}
	else
	{
		i_dig = ft_recur_write(ptr_res, n / base_len, nb_dig + 1, base);
		if (i_dig == 0)
			return (0);
		(*ptr_res)[i_dig] = base[n % base_len];
		return (i_dig + 1);
	}
}
