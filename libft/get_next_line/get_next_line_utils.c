/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausann>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:28:37 by tplanes           #+#    #+#             */
/*   Updated: 2022/11/09 14:28:51 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Extend string s (size s_len) of n more bytes with new alloc and copy
n chars from buff, also set copied buff chars to -1 */
char	*extendn_copy(char *s, int *s_len, char *buff, int n)
{
	char	*out;
	int		i;

	out = (char *)malloc(*s_len + n + 1);
	if (out == NULL)
	{	
		free(s);
		return (NULL);
	}
	out[*s_len + n] = '\0';
	i = 0;
	while (i < *s_len)
	{
		out[i] = s[i];
		i++;
	}
	i = 0;
	while (i < n)
	{	
		out[*s_len + i] = buff[i];
		buff[i++] = -1;
	}
	*s_len = *s_len + n;
	free(s);
	return (out);
}
