/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:25:42 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/16 14:49:38 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int erase_minimap_dirline(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.end.x += game->player.dir.x;
	line.end.y += game->player.dir.y;
	draw_minimap_line(line.start, line.end, 0);
	return (0);
}

int	erase_minimap_fov(void)
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
	draw_minimap_line(line.start, line.end, 0);
	return (0);
}

int	erase_minimap_ray(void)
{
	t_game		*game;
	t_player	*player;
	t_line		line;
	int			i;
	int			w = 20;

	game = get_game_struct();
	player = &(game->player);
	line.start = game->player.pos;
	line.end = game->player.pos;
	i = 0;
	while (i <= w)
	{
		double cameraX = 2 * i / (double)(w) - 1;
		line.end.x = player->pos.x + player->dir.x + player->plane.x * cameraX;
		line.end.y = player->pos.y + player->dir.y + player->plane.y * cameraX;
		draw_minimap_line(line.start, line.end, 0);
		i += 1;
	}
	return (0);
}

int	erase_minimap_player(void)
{
	t_game		*game;
	t_vector	start;
	t_vector	end;

	game = get_game_struct();
	start.x = game->player.pos.x - (MINIMAP_PLAYER_SIZE / 2);
	start.y = game->player.pos.y - (MINIMAP_PLAYER_SIZE / 2);
	end.x = game->player.pos.x + (MINIMAP_PLAYER_SIZE / 2);
	end.y = game->player.pos.y + (MINIMAP_PLAYER_SIZE / 2);
	draw_rect(start, end, 0);
	return (0);
}
