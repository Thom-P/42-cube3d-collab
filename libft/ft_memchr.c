/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:17:14 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:04:17 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*us;

	us = (unsigned char *)s;
	while (n--)
	{
		if (*us == (unsigned char)c)
			return ((void *)us);
		us++;
	}
	return (NULL);
}
