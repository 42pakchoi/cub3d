/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_fov.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:24:58 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/15 18:25:07 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_minimap_fov(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.start.x += game->player.dir.x - game->player.plane.x;
	line.start.y += game->player.dir.y - game->player.plane.y;
	line.end.x += game->player.dir.x + game->player.plane.x;
	line.end.y += game->player.dir.y + game->player.plane.y;
	draw_minimap_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
	return (0);
}
