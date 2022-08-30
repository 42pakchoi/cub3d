/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 03:35:22 by cpak              #+#    #+#             */
/*   Updated: 2022/08/29 18:17:49 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_point point, int color)
{
	t_game	*game;

	game = get_game_struct();
	mlx_pixel_put(game->mlx, game->win, point.x, point.y, color);
}

void	draw_pixel_line(float m, t_point point, t_point dpoint, int color)
{
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
	draw_pixel(point, color);
}

void	draw_pixel_rect(t_vector start, t_vector end, int color)
{
	t_game	*game;
	int		x;
	int		y;

	game = get_game_struct();
	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		while (y < end.y)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, color);
			y += 1;
		}
		x += 1;
	}
}
