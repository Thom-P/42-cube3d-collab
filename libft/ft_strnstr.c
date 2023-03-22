/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:34:32 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:08:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	hay_len;
	size_t	j;

	needle_len = ft_strlen(needle);
	hay_len = ft_strlen(haystack);
	if (needle_len == 0)
		return ((char *)haystack);
	if (len > hay_len)
		len = hay_len;
	if (len == 0 || len < needle_len)
		return (NULL);
	while (len - needle_len + 1)
	{	
		j = 0;
		while (j < len && j < needle_len && haystack[j] == needle[j])
			j++;
		if (j == needle_len)
			return ((char *)haystack);
		haystack++;
		len--;
	}	
	return (NULL);
}
