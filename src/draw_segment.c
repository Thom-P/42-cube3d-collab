/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tplanes <tplanes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:55:28 by tplanes           #+#    #+#             */
/*   Updated: 2023/03/20 17:27:34 by tplanes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	get_next_pix(t_ipt2 *p0, t_ipt2 *p1, t_draw *d);

static void	put_pix_image(t_image *im, int x, int y, int color);

/* 
Bresenham's line algo using integer computations only
Only used in 2D map if SHOW_RAYS flag active 
*/
void	draw_line_image(t_ipt2 *p0, t_ipt2 *p1, t_image *im, int color)
{
	t_draw	d;
	t_ipt2	p0_cpy;

	p0_cpy.x = p0 -> x;
	p0_cpy.y = p0 -> y;
	d.dx = abs(p1 -> x - p0 -> x);
	if (p0 -> x < p1 -> x)
		d.sx = 1;
	else
		d.sx = -1;
	d.dy = -abs(p1 -> y - p0 -> y);
	if (p0 -> y < p1 -> y)
		d.sy = 1;
	else
		d.sy = -1;
	d.error = d.dx + d.dy;
	while (1)
	{
		put_pix_image(im, p0_cpy.x, p0_cpy.y, color);
		if (get_next_pix(&p0_cpy, p1, &d))
			break ;
	}
	return ;
}

// A copy of p0 is provided so that point is not modified during drawing
static int	get_next_pix(t_ipt2 *p0, t_ipt2 *p1, t_draw *d)
{
	int	e2;

	if (p0 -> x == p1 -> x && p0 -> y == p1 -> y)
		return (1);
	e2 = 2 * d -> error;
	if (e2 >= d -> dy)
	{
		if (p0 -> x == p1 -> x)
			return (1);
		d -> error += d -> dy;
		p0 -> x += d -> sx;
	}
	if (e2 <= d -> dx)
	{
		if (p0 -> y == p1 -> y)
			return (1);
		d -> error += d -> dx;
		p0 -> y += d -> sy;
	}
	return (0);
}

static void	put_pix_image(t_image *im, int x, int y, int color)
{
	char	*pix_addr;

	pix_addr = im -> addr + y * im -> line_size + x * (im -> bpp / 8);
	*((unsigned int *)pix_addr) = (unsigned int)color;
	return ;
}
