/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bres_algo_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:20:03 by cpak              #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	put_image_line(float m, t_point point, t_point dpoint)
{
	t_img	*image;

	image = get_game_struct()->minimap;
	if (m > 1)
	{
		point.x += dpoint.y;
		point.y += dpoint.x;
	}
	else
	{
		point.x += dpoint.x;
		point.y += dpoint.y;
	}
	put_image_pixel(image, (int)point.x, (int)point.y, MINIMAP_RAY_COLOR);
}

static void	init_bres_algo(int *f, int *df1, int *df2, t_size size)
{
	*f = 2 * size.h - size.w;
	*df1 = 2 * size.h;
	*df2 = 2 * (size.h - size.w);
}

void	bres_algo(t_bres bres, int is_sub)
{
	int		f;
	int		df1;
	int		df2;
	t_point	dpoint;

	init_bres_algo(&f, &df1, &df2, bres.size);
	dpoint.x = 0;
	dpoint.y = 0;
	while (dpoint.x <= bres.max)
	{
		put_image_line(bres.m, bres.point, dpoint);
		if (f < 0)
			f += df1;
		else
		{
			if (is_sub)
				dpoint.y -= 1;
			else
				dpoint.y += 1;
			f += df2;
		}
		dpoint.x += 1;
	}
}
