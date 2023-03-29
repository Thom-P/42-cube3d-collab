/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:02:02 by saeby             #+#    #+#             */
/*   Updated: 2023/03/29 12:42:52 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	msg_exit(char *msg)
{
	ft_printf(2, "%s\n", msg);
	exit(1);
}

int	get_door(char *path, t_meta *meta)
{
	meta->input.door_path = ft_strdup(path);
	meta->input.door_path[ft_strlen(path) - 1] = 0;
	if (open(meta->input.door_path, O_RDONLY) < 0)
		msg_exit("Unable to open Door texture.");
	return (0);
}

int	get_map_info(char *in_file, t_meta *meta)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(in_file, O_RDONLY);
	line = skip_textures(fd);
	while (1)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
		if (line_nok(line, meta))
		{
			close(fd);
			free(line);
			return (msg_exit("Unauthorized character found."));
		}
		free(line);
		meta->input.m++;
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	close(fd);
	return (0);
}

void	print_map(t_meta *meta)
{
	int	x;
	int	y;

	y = 0;
	while (y < meta->input.m)
	{
		x = 0;
		while (x < meta->input.n)
		{
			ft_putchar_fd(meta->input.map[x + y * meta->input.n], 1);
			x++;
		}
		ft_putchar_fd('\n', 1);
		y++;
	}
}

// parsing done in two steps
// 1: get all information as strings 
// (textures paths, floor/ceiling color as r,g,b, etc)
// 2: convert the values in the expected format and free 
// the memory allocated for the different strings
int	parse_map(char *in_file, t_meta *meta)
{
	int		fd;

	fd = open(in_file, O_RDONLY);
	if (fd < 0)
		return (msg_exit("Unable to open map file."));
	close(fd);
	if (check_filename(in_file))
		return (msg_exit("Wrong map filename (has to end with .cub."));
	meta->input.textures = malloc(5 * sizeof(t_image));
	if (!meta->input.textures)
		return (msg_exit("Error when allocating texture memory."));
	if (parse_textures(in_file, meta))
		return (msg_exit("Unable to parse one of the wall texture."));
	convert_colors(meta);
	free(meta->input.f_color);
	free(meta->input.c_color);
	get_map_info(in_file, meta);
	meta->input.map = ft_calloc((unsigned int)(meta->input.n * meta->input.m), \
				sizeof(char));
	if (!meta->input.map)
		return (1);
	fill_map(in_file, meta);
	check_map(meta);
	return (0);
}

// print_map(meta);