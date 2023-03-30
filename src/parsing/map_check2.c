/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:21:00 by saeby             #+#    #+#             */
/*   Updated: 2023/03/30 14:42:57 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_format(char *rgb_str, t_meta *meta)
{
	int	i;

	i = 0;
	if (!rgb_str)
		free_and_exit("No color found.", meta);
	i = check_value(rgb_str, (unsigned int) i, meta);
	if (i < 0 || rgb_str[i++] != ',')
		return (1);
	i = check_value(rgb_str, (unsigned int) i, meta);
	if (i < 0 || rgb_str[i++] != ',')
		return (1);
	i = check_value(rgb_str, (unsigned int) i, meta);
	if (i < 0)
		return (1);
	return (0);
}

int	check_top_bottom(t_meta *meta)
{
	int	x;

	x = 0;
	while (x < meta->input.n)
	{
		if (meta->input.map[x] == '0')
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

int	check_value(char *rgb_str, unsigned int i, t_meta *meta)
{
	unsigned int	j;
	char			*tmp_str;
	int				tmp;

	j = i;
	while (ft_isdigit(rgb_str[i]))
		i++;
	if (i - j == 0 || i - j > 3)
		free_and_exit("No number or Number too big.", meta);
	tmp_str = ft_substr(rgb_str, j, 3);
	if (tmp_str == NULL)
		free_and_exit("In check_value", meta);
	tmp = ft_atoi(tmp_str);
	free(tmp_str);
	if (tmp < 0 || tmp > 255)
		return (-1);
	return ((int) i);
}

int	line_nok(char *line, t_meta *meta)
{
	if (!line)
		free_and_exit("Error when trimming line", meta);
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
	return (0);
}
