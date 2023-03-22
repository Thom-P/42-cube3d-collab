/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:36:49 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/24 14:07:19 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	n_s1;
	size_t	n_s2;
	char	*s_out;

	n_s1 = ft_strlen(s1);
	n_s2 = ft_strlen(s2);
	s_out = (char *)malloc(n_s1 + n_s2 + 1);
	if (s_out == NULL)
		return (NULL);
	ft_strlcpy(s_out, s1, n_s1 + n_s2 + 1);
	ft_strlcat(s_out, s2, n_s1 + n_s2 + 1);
	return (s_out);
}
