/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:52:53 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/22 14:35:32 by tplanes          ###   ########.fr       */
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

	printf("entereddd\n");
	if (theta_p > PI / 4 && theta_p <= 3 * PI / 4
			&& meta -> play.y % PIX_PER_BLOCK > PIX_PER_BLOCK / 2) //look down and close enough
		i_block++;
	else if (theta_p > 3 * PI / 4 && theta_p <= 5 * PI / 4
			&& meta -> play.x % PIX_PER_BLOCK < PIX_PER_BLOCK / 2) // looking left and close enough
 		j_block--;
	else if (theta_p > 5 * PI / 4 && theta_p <= 7 * PI / 4
			&& meta -> play.y % PIX_PER_BLOCK < PIX_PER_BLOCK / 2) // looking up and close enough
		i_block--;
	else if (meta -> play.x % PIX_PER_BLOCK > PIX_PER_BLOCK / 2) // looking right and close enough
 		j_block++;
	if (meta -> input.map[i_block][j_block] == 2)
	{
		meta -> input.map[i_block][j_block] = 3;
		printf("switched\n");
	}
	else if (meta -> input.map[i_block][j_block] == 3)
	{
		meta -> input.map[i_block][j_block] = 2;
		printf("switched\n");
	}
	return ;
}
