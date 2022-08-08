/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 03:35:22 by cpak              #+#    #+#             */
/*   Updated: 2022/08/06 03:35:41 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pixel(t_point point, int color)
{
	t_game	*game;

	game = get_game_struct();
	mlx_pixel_put(game->mlx, game->win, point.x, point.y, color);
}
