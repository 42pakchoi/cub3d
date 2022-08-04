/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:54:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/04 13:37:30 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_game *data, t_vector start, t_vector end, int color)
{
	int	x;
	int y;

	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		while (y < end.y)
		{
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			y += 1;
		}
		x += 1;
	}
}
