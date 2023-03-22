/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:36:15 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:09:39 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	n_cpy;
	size_t	s_len;
	char	*s_out;

	s_len = ft_strlen(s);
	if (len == 0 || s_len == 0 || start > s_len - 1)
	{
		s_out = (char *)malloc(1);
		if (s_out == NULL)
			return (NULL);
		s_out[0] = '\0';
		return (s_out);
	}
	if (s_len - start < len)
		n_cpy = s_len - start;
	else
		n_cpy = len;
	s_out = (char *)malloc(n_cpy + 1);
	if (s_out == NULL)
		return (NULL);
	s_out[n_cpy] = 0;
	while (n_cpy--)
		s_out[n_cpy] = s[start + n_cpy];
	return (s_out);
}
