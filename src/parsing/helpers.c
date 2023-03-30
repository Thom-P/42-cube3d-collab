/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:39:06 by saeby             #+#    #+#             */
/*   Updated: 2023/03/30 14:17:11 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*skip_textures(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd); //need to protect in case line = NULL?
		if (!(!ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2) || \
			!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) || \
			!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1) || \
			!ft_strncmp(line, "D", 1) || !ft_strncmp(line, "\n", 1)))
			break ;
		free(line);
	}
	return (line);
}

char	*set_spaces(char *line, t_meta *meta)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(line);
	while (len < (unsigned int) meta->input.n)
	{
		tmp = line;
		line = ft_strjoin(line, " ");  //malloc
		free(tmp);
		len++;
	}
	return (line);
}

int	fill_map(char *in_file, t_meta *meta)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(in_file, O_RDONLY); //protect open
	line = skip_textures(fd);
	while (1)
	{
		tmp = line;
		line = ft_strtrim(line, "\n"); //malloc 
		free(tmp);
		tmp = meta->input.map;
		if (ft_strlen(line) < (unsigned int) meta->input.n)
			line = set_spaces(line, meta);
		meta->input.map = ft_strjoin(tmp, line); //malloc
		free(tmp);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	close (fd);
	return (0);
}

int	is_dir(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

int	set_start(int x, int y, t_meta *meta)
{
	if (meta->input.p_j != 0 || meta->input.p_i != 0)
		free_and_exit("Multiple start position found on map.", meta);
	meta->input.p_j = x;
	meta->input.p_i = y;
	meta->input.p_dir = meta->input.map[x + y * meta->input.n];
	meta->input.map[x + y * meta->input.n] = '0';
	return (0);
}
