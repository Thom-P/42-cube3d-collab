/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:23:25 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:06:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	ptr = (char *)malloc(s1_len + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[s1_len] = 0;
	while (s1_len--)
		ptr[s1_len] = s1[s1_len];
	return (ptr);
}
