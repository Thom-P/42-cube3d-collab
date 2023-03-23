/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:52:53 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/23 10:44:17 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	try_switch_door(t_meta *meta)
{
	float	theta_p;
	int		i_block;
	int		j_block;

	theta_p = meta -> play.theta; // player wiew angle
	i_block = meta -> play.y / PIX_PER_BLOCK; //i index of block player is in
 	j_block = meta -> play.x / PIX_PER_BLOCK; //j index of block player is in

	if (theta_p > PI / 4 && theta_p <= 3 * PI / 4) //looking down
		i_block++;
	else if (theta_p > 3 * PI / 4 && theta_p <= 5 * PI / 4) // looking left 
 		j_block--;
	else if (theta_p > 5 * PI / 4 && theta_p <= 7 * PI / 4) // looking up
		i_block--;
	else //looking right
 		j_block++;
	if (meta -> input.map[i_block * meta -> input.n + j_block] == '2')
		meta -> input.map[i_block * meta -> input.n + j_block] = '3';
	else if (meta -> input.map[i_block * meta -> input.n + j_block] == '3')
		meta -> input.map[i_block * meta -> input.n + j_block] = '2';
	return ;
}
