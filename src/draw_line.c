/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:08:31 by cpak              #+#    #+#             */
/*   Updated: 2022/08/04 13:40:29 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_line(t_game *data, t_vector start, t_vector end, int color)
{
	int dx = fabs(end.x - start.x);
	int dy = fabs(end.y - start.y);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy;
	int twoDyMinusDx = 2 * (dy - dx);
	int x;
	int y;

	if (start.x > end.x)
	{
		x = end.x;
		y = end.y;
		end.x = start.x;
	}
	else
	{
		x = start.x;
		y = start.y; 
	}
	mlx_pixel_put(data->mlx, data->win, x, y, color);
	while (x < end.x)
	{
		x++;
		if (p < 0)
			p += twoDy;
		else
		{
			y++;
			p += twoDyMinusDx;
		}
		mlx_pixel_put(data->mlx, data->win, x, y, color);
	}
}
