/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:06 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:03:57 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_recur_write(char **ptr_res, int n, int nb_dig, int is_neg);

char	*ft_itoa(int n)
{
	char	*res;

	if (ft_recur_write(&res, n, 1, n < 0) == 0)
		return (NULL);
	return (res);
}

static int	ft_recur_write(char **ptr_res, int n, int nb_dig, int is_neg)
/* Returns index of next digit to write */
{
	int	i_dig;

	if ((!is_neg && n <= 9) || (is_neg && n >= -9))
	{
		*ptr_res = (char *)malloc(nb_dig + is_neg + 1);
		if (*ptr_res == NULL)
			return (0);
		(*ptr_res)[0] = '-';
		(*ptr_res)[0 + is_neg] = (char)(-(is_neg * 2 - 1) * n + '0');
		(*ptr_res)[nb_dig + is_neg] = '\0';
		return (is_neg + 1);
	}
	else
	{
		i_dig = ft_recur_write(ptr_res, n / 10, nb_dig + 1, is_neg);
		if (i_dig == 0)
			return (0);
		(*ptr_res)[i_dig] = (char)(-(is_neg * 2 - 1) * (n % 10) + '0');
		return (i_dig + 1);
	}
}
