/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:15:25 by saeby             #+#    #+#             */
/*   Updated: 2023/03/29 12:45:03 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_text_filename(char **tmp)
{
	size_t	len;

	len = ft_strlen(tmp[1]) - 2;
	if (!(tmp[1][len - 3] == '.'
		&& tmp[1][len - 2] == 'x'
		&& tmp[1][len - 1] == 'p'
		&& tmp[1][len] == 'm'))
		return (1);
	return (0);
}

int	check_filename(char *in_file)
{
	size_t	len;

	len = ft_strlen(in_file) - 1;
	if (!(in_file[len - 3] == '.'
			&& in_file[len - 2] == 'c'
			&& in_file[len - 1] == 'u'
			&& in_file[len] == 'b'))
		return (1);
	return (0);
}
