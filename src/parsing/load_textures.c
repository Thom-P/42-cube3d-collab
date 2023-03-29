/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:25:05 by saeby             #+#    #+#             */
/*   Updated: 2023/03/29 14:32:03 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	load_textures(t_meta *meta)
{
	load_xpm_files(meta);
	if (!meta->input.textures[0].id
		|| !meta->input.textures[1].id
		|| !meta->input.textures[2].id
		|| !meta->input.textures[3].id
		|| !meta->input.textures[4].id)
		return (1);
	get_text_addr(meta);
	free(meta->input.no_path);
	free(meta->input.so_path);
	free(meta->input.ea_path);
	free(meta->input.we_path);
	free(meta->input.door_path);
	return (0);
}

int	parse_textures(char *in_file, t_meta *meta)
{
	int		fd;
	char	*line;

	fd = open(in_file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strncmp(line, "NO", 2))
			get_texture_path(NO, line, meta);
		if (!ft_strncmp(line, "SO", 2))
			get_texture_path(SO, line, meta);
		if (!ft_strncmp(line, "EA", 2))
			get_texture_path(EA, line, meta);
		if (!ft_strncmp(line, "WE", 2))
			get_texture_path(WE, line, meta);
		if (!ft_strncmp(line, "D", 1))
			get_texture_path(D, line, meta);
		parse_colors(line, meta);
		free(line);
	}
	close(fd);
	return (0);
}

void	load_xpm_files(t_meta *meta)
{
	meta->input.textures[0].id = mlx_xpm_file_to_image(meta->xp.mlx, \
								meta->input.no_path, \
								&(meta->input.textures[0].nx), \
								&(meta->input.textures[0].ny));
	meta->input.textures[1].id = mlx_xpm_file_to_image(meta->xp.mlx, \
								meta->input.so_path, \
								&(meta->input.textures[1].nx), \
								&(meta->input.textures[1].ny));
	meta->input.textures[2].id = mlx_xpm_file_to_image(meta->xp.mlx, \
								meta->input.ea_path, \
								&(meta->input.textures[2].nx), \
								&(meta->input.textures[2].ny));
	meta->input.textures[3].id = mlx_xpm_file_to_image(meta->xp.mlx, \
								meta->input.we_path, \
								&(meta->input.textures[3].nx), \
								&(meta->input.textures[3].ny));
	meta->input.textures[4].id = mlx_xpm_file_to_image(meta->xp.mlx, \
								meta->input.door_path, \
								&(meta->input.textures[4].nx), \
								&(meta->input.textures[4].ny));
	load_sprites(meta);
}

void	get_addr_1(t_meta *meta)
{
	meta->input.textures[0].addr = (char *)mlx_get_data_addr(\
									meta->input.textures[0].id, \
									&meta->input.textures[0].bpp, \
									&meta->input.textures[0].line_size, \
									&meta->input.textures[0].endian);
	meta->input.textures[1].addr = (char *)mlx_get_data_addr(\
									meta->input.textures[1].id, \
									&meta->input.textures[1].bpp, \
									&meta->input.textures[1].line_size, \
									&meta->input.textures[1].endian);
	meta->input.textures[2].addr = (char *)mlx_get_data_addr(\
									meta->input.textures[2].id, \
									&meta->input.textures[2].bpp, \
									&meta->input.textures[2].line_size, \
									&meta->input.textures[2].endian);
}

void	get_text_addr(t_meta *meta)
{
	get_addr_1(meta);
	meta->input.textures[3].addr = (char *)mlx_get_data_addr(\
									meta->input.textures[3].id, \
									&meta->input.textures[3].bpp, \
									&meta->input.textures[3].line_size, \
									&meta->input.textures[3].endian);
	meta->input.textures[4].addr = (char *)mlx_get_data_addr(\
									meta->input.textures[4].id, \
									&meta->input.textures[4].bpp, \
									&meta->input.textures[4].line_size, \
									&meta->input.textures[4].endian);
	get_sprite_addr(meta);
}
