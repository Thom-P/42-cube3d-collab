/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saeby <saeby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:12:52 by saeby             #+#    #+#             */
/*   Updated: 2023/03/29 12:33:19 by saeby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_udr(int x, int y, t_meta *meta)
{
	return (meta->input.map[x + y * meta->input.n] == ' '
		|| meta->input.map[x + (y + 1) * meta->input.n] == ' '
		|| meta->input.map[(x + 1) + y * meta->input.n] == ' ');
}

int	check_udl(int x, int y, t_meta *meta)
{
	return (meta->input.map[x + (y - 1) * meta->input.n] == ' '
		|| meta->input.map[x + (y + 1) * meta->input.n] == ' '
		|| meta->input.map[(x + 1) + y * meta->input.n] == ' ');
}

int	check_udlr(int x, int y, t_meta *meta)
{
	return (meta->input.map[x + (y - 1) * meta->input.n] == ' '
		|| meta->input.map[x + (y + 1) * meta->input.n] == ' '
		|| meta->input.map[(x - 1) + y * meta->input.n] == ' '
		|| meta->input.map[(x + 1) + y * meta->input.n] == ' ');
}

int	space_around(int x, int y, t_meta *meta)
{
	if (x == 0)
	{
		if (check_udr(x, y, meta))
			free_and_exit("Map not eclosed in walls.", meta);
	}
	else if (x == meta->input.n - 1)
	{
		if (check_udl(x, y, meta))
			free_and_exit("Map not enclosed in walls.", meta);
	}
	else
	{
		if (check_udlr(x, y, meta))
			free_and_exit("Map not eclosed in walls.", meta);
	}
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
		free_and_exit("Map not enclosed in walls.", meta);
	y = 1;
	while (y < meta->input.m - 1)
	{
		x = 0;
		while (x < meta->input.n)
		{
			if (meta->input.map[x + y * meta->input.n] == '0'
				|| meta->input.map[x + y * meta->input.n] == '2'
				|| meta->input.map[x + y * meta->input.n] == '3')
				space_around(x, y, meta);
			if (is_dir(meta->input.map[x + y * meta->input.n]))
				set_start(x, y, meta);
			x++;
		}
		y++;
	}
	return (0);
}
