/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:04:10 by saeby             #+#    #+#             */
/*   Updated: 2023/03/29 12:19:22 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_north(char *path, t_meta *meta)
{
	meta->input.no_path = ft_strdup(path);
	meta->input.no_path[ft_strlen(path) - 1] = 0;
	if (open(meta->input.no_path, O_RDONLY) < 0)
		free_and_exit("Unable to open North texture", meta);
	return (0);
}

int	get_south(char *path, t_meta *meta)
{
	meta->input.so_path = ft_strdup(path);
	meta->input.so_path[ft_strlen(path) - 1] = 0;
	if (open(meta->input.so_path, O_RDONLY) < 0)
		free_and_exit("Unable to open South texture", meta);
	return (0);
}

int	get_west(char *path, t_meta *meta)
{
	meta->input.we_path = ft_strdup(path);
	meta->input.we_path[ft_strlen(path) - 1] = 0;
	if (open(meta->input.we_path, O_RDONLY) < 0)
		free_and_exit("Unable to open West texture", meta);
	return (0);
}

int	get_east(char *path, t_meta *meta)
{
	meta->input.ea_path = ft_strdup(path);
	meta->input.ea_path[ft_strlen(path) - 1] = 0;
	if (open(meta->input.ea_path, O_RDONLY) < 0)
		free_and_exit("Unable to open East texture", meta);
	return (0);
}

int	get_texture_path(int dir, char *line, t_meta *meta)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (check_text_filename(tmp))
		free_and_exit("Texture isn't a .xpm file", meta);
	if (dir == NO)
		get_north(tmp[1], meta);
	else if (dir == SO)
		get_south(tmp[1], meta);
	else if (dir == WE)
		get_west(tmp[1], meta);
	else if (dir == EA)
		get_east(tmp[1], meta);
	else if (dir == D)
		get_door(tmp[1], meta);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (0);
}
