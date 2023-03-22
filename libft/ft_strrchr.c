/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:52:28 by tplanes           #+#    #+#             */
/*   Updated: 2022/10/20 12:12:40 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;

	res = 0;
	while (*s != 0)
	{
		if (*s == (char)c)
			res = (char *) s;
		s++;
	}
	if ((char)c != 0)
		return (res);
	return ((char *) s);
}
