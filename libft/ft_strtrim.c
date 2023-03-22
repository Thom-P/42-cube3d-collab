/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:37:21 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:09:18 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	n_s;
	char	*s_out;

	while (*s1 && ft_is_in_set(*s1, set))
		s1++;
	if (*s1 == 0)
	{
		s_out = (char *)malloc(1);
		if (s_out == 0)
			return (NULL);
		s_out[0] = '\0';
		return (s_out);
	}
	n_s = ft_strlen(s1);
	n_s--;
	while (ft_is_in_set(s1[n_s], set))
		n_s--;
	s_out = (char *)malloc((n_s + 1) + 1);
	if (s_out == NULL)
		return (NULL);
	ft_strlcpy(s_out, s1, (n_s + 1) + 1);
	return (s_out);
}

static int	ft_is_in_set(char c, char const *set)
{
	while (*set)
	{	
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
