/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:08:31 by cpak              #+#    #+#             */
/*   Updated: 2022/08/12 17:35:32 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bres_algo(t_point point, t_size size, float m, int is_sub, int color, int max)
{
	int		f;
	int		df1;
	int		df2;
	t_point	dpoint;
	t_img	*image;

	image = get_game_struct()->minimap;
	f = 2 * size.h - size.w;
	df1 = 2 * size.h;
	df2 = 2 * (size.h - size.w);
	dpoint.x = 0;
	dpoint.y = 0;
	while (dpoint.x <= max)
	{
		put_image_line(image, m, point, dpoint, color);
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

static void	put_quadrant_one_four(t_vector start, t_vector end, int color)
{
	t_point	point;
	t_size	size;
	float	m;
	int		max;

	point.x = start.x;
	point.y = start.y;
	size.w = end.x - start.x;
	size.h = end.y - start.y;
	m = (float)size.h / (float)size.w;
	if (m > 1)
	{
		ft_swap_int(&size.w, &size.h);
		max = end.y - point.y;
	}
	else
		max = end.x - point.x;
	bres_algo(point, size, m, 0, color, max);
}

static void	put_quadrant_two_three(t_vector start, t_vector end, int color)
{
	t_point	point;
	t_size	size;
	float	m;
	int		max;

	point.x = start.x;
	point.y = start.y;
	size.w = end.x - start.x;
	size.h = end.y - start.y;
	size.w *= -1;
	m = (float)size.h / (float)size.w;
	if (m > 1)
	{
		ft_swap_int(&size.w, &size.h);
		max = end.y - point.y;
	}
	else
	{
		point.x = end.x;
		point.y = end.y;
		max = start.x - point.x;
	}
	bres_algo(point, size, m, 1, color, max);
}

void	put_minimap_line(t_vector start, t_vector end, int color)
{
	t_game *game;
	int	w;
	int	h;

	game = get_game_struct();
	start.x *= game->map.minimap_tile_size;
	start.y *= game->map.minimap_tile_size;
	end.x *= game->map.minimap_tile_size;
	end.y *= game->map.minimap_tile_size;

	w = end.x - start.x;
	h = end.y - start.y;
	if (w >= 0 && h >= 0)
		put_quadrant_one_four(start, end, color);
	else if (w <= 0 && h <= 0)
		put_quadrant_one_four(end, start, color);
	else if (w < 0)
		put_quadrant_two_three(start, end, color);
	else if (h < 0)
		put_quadrant_two_three(end, start, color);
}
