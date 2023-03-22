/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:32:31 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:07:31 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dst_size == 0 || dst_len > dst_size)
		return (dst_size + src_len);
	i = dst_len;
	while (i < dst_size - 1 && *src)
		dst[i++] = *src++;
	dst[i] = 0;
	return (dst_len + src_len);
}
