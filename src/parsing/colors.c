/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:23:25 by saeby             #+#    #+#             */
/*   Updated: 2023/03/30 14:38:08 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_color(int dir, char *line, t_meta *meta)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (tmp == NULL)
		free_and_exit("In get_color", meta);
	if (dir == F)
	{
		meta->input.f_color = ft_strdup(tmp[1]);
		if (meta->input.f_color == NULL)
			free_and_exit("In get_color", meta);
		meta->input.f_color[ft_strlen(tmp[1]) - 1] = 0;
	}
	else if (dir == C)
	{
		meta->input.c_color = ft_strdup(tmp[1]);
		if (meta->input.c_color == NULL)
			free_and_exit("In get_color", meta);
		meta->input.c_color[ft_strlen(tmp[1]) - 1] = 0;
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (0);
}

int	parse_colors(char *line, t_meta *meta)
{
	if (!ft_strncmp(line, "F", 1))
		get_color(F, line, meta);
	if (!ft_strncmp(line, "C", 1))
		get_color(C, line, meta);
	return (0);
}

int	convert_color(char **c)
{
	int	tmp;

	tmp = (ft_atoi(c[0]) << 16) | (ft_atoi(c[1]) << 8) | ft_atoi(c[2]);
	free(c[0]);
	free(c[1]);
	free(c[2]);
	free(c);
	return (tmp);
}

int	convert_colors(t_meta *meta)
{
	char	**tmp;

	if (check_format(meta->input.c_color, meta))
		free_and_exit("Wrong format for ceiling color.", meta);
	if (check_format(meta->input.f_color, meta))
		free_and_exit("Wrong format for floor color.", meta);
	tmp = ft_split(meta->input.f_color, ',');
	if (tmp == NULL)
		free_and_exit("In convert_colors", meta);
	meta->input.floor = convert_color(tmp);
	tmp = ft_split(meta->input.c_color, ',');
	if (tmp == NULL)
		free_and_exit("In convert_colors", meta);
	meta->input.ceiling = convert_color(tmp);
	return (0);
}
