/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:02:02 by saeby             #+#    #+#             */
/*   Updated: 2023/03/23 13:13:41 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	msg_exit(char *msg)
{
	ft_printf(2, "%s\n", msg);
	exit(1);
}

int	line_nok(char *line, t_meta *meta)
{
	while (*line)
	{
		if (!(*line == '0' || *line == '1' || *line == '2' || *line == 'N' 
			|| *line == '3' || *line == 'S' || *line == 'W' || *line == 'E' 
			|| *line == ' '))
			return (1);
		if (ft_strlen(line) >= (unsigned int) meta->input.n)
			meta->input.n = (int) ft_strlen(line);
		line++;
	}
	// ft_printf(1, "Line len(meta->input.n): %d\n", meta->input.n);
	return (0);
}

int	check_text_filename(char **tmp)
{
	size_t	len;

	len = ft_strlen(tmp[1]) - 2;
	if (!(tmp[1][len - 3] == '.' && 
			tmp[1][len - 2] == 'x' && 
			tmp[1][len - 1] == 'p' && 
			tmp[1][len] == 'm'))
		msg_exit("Wrong texture filename.");
	return (0);
}

int	get_texture_path(int dir, char *line, t_meta *meta)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (check_text_filename(tmp))
		return (msg_exit("Texture isn't a .xpm file."));
	if (dir == NO)
	{
		meta->input.no_path = ft_strdup(tmp[1]);
		meta->input.no_path[ft_strlen(tmp[1]) - 1] = 0;
		if (open(meta->input.no_path, O_RDONLY) < 0)
			msg_exit("Unable to open North texture.");
	}
	else if (dir == SO)
	{
		meta->input.so_path = ft_strdup(tmp[1]);
		meta->input.so_path[ft_strlen(tmp[1]) - 1] = 0;
		if (open(meta->input.so_path, O_RDONLY) < 0)
			msg_exit("Unable to open South texture.");
	}
	else if (dir == WE)
	{
		meta->input.we_path = ft_strdup(tmp[1]);
		meta->input.we_path[ft_strlen(tmp[1]) - 1] = 0;
		if (open(meta->input.we_path, O_RDONLY) < 0)
			msg_exit("Unable to open West texture.");
	}
	else if (dir == EA)
	{
		meta->input.ea_path = ft_strdup(tmp[1]);
		meta->input.ea_path[ft_strlen(tmp[1]) - 1] = 0;
		if (open(meta->input.ea_path, O_RDONLY) < 0 )
			msg_exit("Unable to open East texture.");
	}
	else if (dir == D)
	{
		meta->input.door_path = ft_strdup(tmp[1]);
		meta->input.door_path[ft_strlen(tmp[1]) - 1] = 0;
		if (open(meta->input.door_path, O_RDONLY) < 0)
			msg_exit("Unable to open Door texture.");
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (0);
}

int	get_color(int dir, char *line, t_meta *meta)
{
	char	**tmp;

	tmp = ft_split(line, ' ');
	if (dir == F)
	{
		meta->input.f_color = ft_strdup(tmp[1]);
		meta->input.f_color[ft_strlen(tmp[1]) - 1] = 0;
	}
	else if (dir == C)
	{
		meta->input.c_color = ft_strdup(tmp[1]);
		meta->input.c_color[ft_strlen(tmp[1]) - 1] = 0;
	}
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (0);
}

int	check_filename(char *in_file)
{
	size_t	len;

	len = ft_strlen(in_file) - 1;
	if (!(in_file[len - 3] == '.' &&
				 in_file[len - 2] == 'c' &&
				 in_file[len - 1] == 'u' &&
				 in_file[len] == 'b'))
		return (1);
	// ft_printf(2, "valid map filename> %s\n", in_file);
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
			if (get_texture_path(NO, line, meta))
				return (1);
		if (!ft_strncmp(line, "SO", 2))
			if (get_texture_path(SO, line, meta))
				return (1);
		if (!ft_strncmp(line, "EA", 2))
			if (get_texture_path(EA, line, meta))
				return (1);
		if (!ft_strncmp(line, "WE", 2))
			if (get_texture_path(WE, line, meta))
				return (1);
		if (!ft_strncmp(line, "D", 1))
			if (get_texture_path(D, line, meta))
				return (1);
		if (!ft_strncmp(line, "F", 1))
			if (get_color(F, line, meta))
				return (1);
		if (!ft_strncmp(line, "C", 1))
			if (get_color(C, line, meta))
				return (1);
		free(line);
	}
	close(fd);
	return (0);
}

int	check_value(char *rgb_str, unsigned int i)
{
	unsigned int	j;
	char			*tmp_str;
	int				tmp;

	j = i;
	while (ft_isdigit(rgb_str[i]))
		i++;
	if (i - j == 0 || i - j > 3)
	{
		ft_printf(2, "No number or Number too big\n");
		return (-1);
	}
	tmp_str = ft_substr(rgb_str, j, 3);
	tmp = ft_atoi(tmp_str);
	free(tmp_str);
	if (tmp < 0 || tmp > 255)
		return (-1);
	return ((int) i);
}

int	check_format(char *rgb_str)
{
	int	i;

	i = 0;
	i = check_value(rgb_str, (unsigned int) i);
	if (i < 0 || rgb_str[i++] != ',')
		return (1);
	i = check_value(rgb_str, (unsigned int) i);
	if (i < 0 || rgb_str[i++] != ',')
		return (1);
	i = check_value(rgb_str, (unsigned int) i);
	if (i < 0)
		return (1);
	return (0);
}

int	convert_colors(t_meta *meta)
{
	char	**tmp;
	int		comp[3];

	if (check_format(meta->input.c_color))
		return (msg_exit("Wrong format for ceiling color"));
	if (check_format(meta->input.f_color))
		return (msg_exit("Wrong format for floor color"));
	tmp = ft_split(meta->input.f_color, ',');
	comp[0] = ft_atoi(tmp[0]);
	comp[1] = ft_atoi(tmp[1]);
	comp[2] = ft_atoi(tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	meta->input.floor = (comp[0] << 16) | (comp[1] << 8) | comp[2];
	tmp = ft_split(meta->input.c_color, ',');
	comp[0] = ft_atoi(tmp[0]);
	comp[1] = ft_atoi(tmp[1]);
	comp[2] = ft_atoi(tmp[2]);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	meta->input.ceiling = (comp[0] << 16) | (comp[1] << 8) | comp[2];
	return (0);
}

int	get_map_info(char *in_file, t_meta *meta)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(in_file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!(!ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2) || \
			!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) || \
			!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1) || \
			!ft_strncmp(line, "D", 1) || !ft_strncmp(line, "\n", 1)))
			break ;
		free(line);
	}
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

int	load_textures(t_meta *meta)
{
	meta->input.textures[0].id = mlx_xpm_file_to_image(meta->xp.mlx, meta->input.no_path, &(meta->input.textures[0].nx), &(meta->input.textures[0].ny));
	meta->input.textures[1].id = mlx_xpm_file_to_image(meta->xp.mlx, meta->input.so_path, &(meta->input.textures[1].nx), &(meta->input.textures[1].ny));
	meta->input.textures[2].id = mlx_xpm_file_to_image(meta->xp.mlx, meta->input.ea_path, &(meta->input.textures[2].nx), &(meta->input.textures[2].ny));
	meta->input.textures[3].id = mlx_xpm_file_to_image(meta->xp.mlx, meta->input.we_path, &(meta->input.textures[3].nx), &(meta->input.textures[3].ny));
	meta->input.textures[4].id = mlx_xpm_file_to_image(meta->xp.mlx, meta->input.door_path, &(meta->input.textures[4].nx), &(meta->input.textures[4].ny));

	if (!meta->input.textures[0].id || !meta->input.textures[1].id || !meta->input.textures[2].id || !meta->input.textures[3].id || !meta->input.textures[4].id)
		return (1);

	meta->input.textures[0].addr = (char *)mlx_get_data_addr(meta->input.textures[0].id, &meta->input.textures[0].bpp, &meta->input.textures[0].line_size, &meta->input.textures[0].endian);
	meta->input.textures[1].addr = (char *)mlx_get_data_addr(meta->input.textures[1].id, &meta->input.textures[1].bpp, &meta->input.textures[1].line_size, &meta->input.textures[1].endian);
	meta->input.textures[2].addr = (char *)mlx_get_data_addr(meta->input.textures[2].id, &meta->input.textures[2].bpp, &meta->input.textures[2].line_size, &meta->input.textures[2].endian);
	meta->input.textures[3].addr = (char *)mlx_get_data_addr(meta->input.textures[3].id, &meta->input.textures[3].bpp, &meta->input.textures[3].line_size, &meta->input.textures[3].endian);
	meta->input.textures[4].addr = (char *)mlx_get_data_addr(meta->input.textures[4].id, &meta->input.textures[4].bpp, &meta->input.textures[4].line_size, &meta->input.textures[4].endian);
	free(meta->input.no_path);
	free(meta->input.so_path);
	free(meta->input.ea_path);
	free(meta->input.we_path);
	free(meta->input.door_path);
	return (0);
}

char	*set_spaces(char *line, t_meta *meta)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(line);
	while (len < (unsigned int) meta->input.n)
	{
		tmp = line;
		line = ft_strjoin(line, " ");
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

	fd = open(in_file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!(!ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "NO", 2) || \
			!ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2) || \
			!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1) || \
			!ft_strncmp(line, "D", 1) || !ft_strncmp(line, "\n", 1)))
			break ;
		free(line);
	}
	while (1)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
		tmp = meta->input.map;
		if (ft_strlen(line) < (unsigned int) meta->input.n)
			line = set_spaces(line, meta);
		meta->input.map = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	close (fd);
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

int	check_udr(int x, int y, t_meta *meta)
{
	return (meta->input.map[x + y * meta->input.n] == ' ' ||
			meta->input.map[x + (y + 1) * meta->input.n] == ' ' ||
			meta->input.map[(x + 1) + y * meta->input.n] == ' ');
}

int	check_udl(int x, int y, t_meta *meta)
{
	return (meta->input.map[x + (y - 1) * meta->input.n] == ' ' ||
			meta->input.map[x + (y + 1) * meta->input.n] == ' ' ||
			meta->input.map[(x + 1) + y * meta->input.n] == ' ');
}

int	check_udlr(int x, int y, t_meta *meta)
{
	return (meta->input.map[x + (y - 1) * meta->input.n] == ' ' ||
			meta->input.map[x + (y + 1) * meta->input.n] == ' ' ||
			meta->input.map[(x - 1) + y * meta->input.n] == ' ' ||
			meta->input.map[(x + 1) + y * meta->input.n] == ' ');
}

int space_around(int x, int y, t_meta *meta)
{
	if (x == 0)
	{
		if (check_udr(x, y, meta))
			return (1);
	}
	else if (x == meta->input.n - 1)
	{
		if (check_udl(x, y, meta))
			return (1);
	}
	else
	{
		if (check_udlr(x, y, meta))
			return (1);
	}
	return (0);
}

int	check_top_bottom(t_meta *meta)
{
	int	x;
	int	y;
	
	y = 0;
	x = 0;
	while (x < meta->input.n)
	{
		if (meta->input.map[x + y * meta->input.n] == '0')
			return (1);
		x++;
	}
	x = 0;
	while (x < meta->input.n)
	{
		if (meta->input.map[x + (meta->input.m - 1) * meta->input.n] == '0')
			return (1);
		x++;
	}
	return (0);
}

int	is_dir(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

int	set_start(int x, int y, t_meta *meta)
{
	if (meta->input.p_j != 0 || meta->input.p_i != 0)
		return (msg_exit("Multiple start position found on map."));
	meta->input.p_j = x;
	meta->input.p_i = y;
	meta->input.p_dir = meta->input.map[x + y * meta->input.n];
	meta->input.map[x + y * meta->input.n] = '0';
	return (0);
}

int	check_map(t_meta *meta)
{
	int	x;
	int	y;

	meta->input.p_i = 0;
	meta->input.p_j = 0;
	meta->input.p_dir = 'N';
	if (check_top_bottom(meta))
		return (1);
	y = 1;
	while (y < meta->input.m - 1)
	{
		x = 0;
		while (x < meta->input.n)
		{
			if (meta->input.map[x + y * meta->input.n] == '0' 
				|| meta->input.map[x + y * meta->input.n] == '2' 
				|| meta->input.map[x + y * meta->input.n] == '3')
				if (space_around(x, y, meta))
					return (msg_exit("Map not enclosed in walls."));
			if (is_dir(meta->input.map[x + y * meta->input.n]))
				if (set_start(x, y, meta))
					return (msg_exit("Error setting player start position."));
			x++;
		}
		y++;
	}
	return (0);
}

/*
 * parsing done in two steps
 * 1: get all information as strings (textures paths, floor/ceiling color as r,g,b, etc)
 * 2: convert the values in the expected format and free the memory allocated for the different strings
*/
int	parse_map(char *in_file, t_meta *meta)
{
	int		fd;
	// char	*map2D;

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
	if (convert_colors(meta))
		return (1/* error when converting rgb to int*/);
	free(meta->input.f_color);
	free(meta->input.c_color);
	if (get_map_info(in_file, meta))
		return (1/* error when getting map information*/);
	meta->input.map = ft_calloc((unsigned int)(meta->input.n * meta->input.m), sizeof(char));
	if (!meta->input.map)
		return (1 /*malloc error*/);
	if (fill_map(in_file, meta))
		return (1/*error when filling map arraz*/);
	// check_map(meta);
	if (check_map(meta))
		return (1/*not a valid map*/);
	print_map(meta);
	return (0);
}
