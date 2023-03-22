/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:39:48 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:08:22 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	char	*s_out;

	s_len = ft_strlen(s);
	s_out = (char *)malloc(s_len + 1);
	if (s_out == NULL)
		return (NULL);
	s_out[s_len] = '\0';
	while (s_len--)
		s_out[s_len] = f((unsigned int)s_len, s[s_len]);
	return (s_out);
}
