/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:52:53 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/23 14:26:38 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	try_switch_door(t_meta *meta)
{
	float	theta_p;
	int		i_block;
	int		j_block;

	theta_p = meta -> play.theta;
	i_block = meta -> play.y / PIX_PER_BLOCK;
	j_block = meta -> play.x / PIX_PER_BLOCK;
	if (theta_p > PI / 4 && theta_p <= 3 * PI / 4)
		i_block++;
	else if (theta_p > 3 * PI / 4 && theta_p <= 5 * PI / 4)
		j_block--;
	else if (theta_p > 5 * PI / 4 && theta_p <= 7 * PI / 4)
		i_block--;
	else
		j_block++;
	if (meta -> input.map[i_block * meta -> input.n + j_block] == '2')
		meta -> input.map[i_block * meta -> input.n + j_block] = '3';
	else if (meta -> input.map[i_block * meta -> input.n + j_block] == '3')
		meta -> input.map[i_block * meta -> input.n + j_block] = '2';
	return ;
}
