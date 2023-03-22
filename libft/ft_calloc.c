/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:33:46 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:02:32 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	n;

	n = count * size;
	ptr = (char *)malloc(n);
	if (ptr == NULL)
		return (NULL);
	while (n--)
		ptr[n] = 0;
	return ((void *)ptr);
}
