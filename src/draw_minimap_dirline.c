/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_dirline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/15 18:20:32 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int draw_minimap_dirline(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.end.x += game->player.dir.x;
	line.end.y += game->player.dir.y;
	draw_minimap_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
	return (0);
}
