/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:26:58 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:04:58 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s_src;
	char	*s_dst;

	s_src = (char *) src;
	s_dst = (char *) dst;
	if (len == 0 || dst == src)
		return (dst);
	if (dst < src)
	{
		while (len--)
			*s_dst++ = *s_src++;
	}
	else
	{
		while (len--)
			*(s_dst + len) = *(s_src + len);
	}	
	return (dst);
}
