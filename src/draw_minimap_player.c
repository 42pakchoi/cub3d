/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/12 18:12:15 by cpak             ###   ########seoul.kr  */
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
	draw_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

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
	draw_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

int	draw_minimap_ray(void)
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
		draw_line(line.start, line.end, MINIMAP_RAY_COLOR);
		i += 1;
	}
	return (0);
}

int	draw_minimap_player(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.start.x *= MINIMAP_PLAYER_HEIGHT;
	line.start.y *= MINIMAP_PLAYER_WIDTH;
	line.end.x *= MINIMAP_PLAYER_HEIGHT;
	line.end.y *= MINIMAP_PLAYER_WIDTH;
	draw_rect(line.start, line.end, MINIMAP_PLAYER_COLOR);
	return (0);
}

int erase_minimap_dirline(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.end.x += game->player.dir.x;
	line.end.y += game->player.dir.y;
	draw_line(line.start, line.end, 0);
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
	draw_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
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
		draw_line(line.start, line.end, MINIMAP_RAY_COLOR);
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
	start.x = game->player.pos.x - (MINIMAP_PLAYER_HEIGHT / 2);
	start.y = game->player.pos.y - (MINIMAP_PLAYER_WIDTH / 2);
	end.x = game->player.pos.x + (MINIMAP_PLAYER_HEIGHT / 2);
	end.y = game->player.pos.y + (MINIMAP_PLAYER_WIDTH / 2);
	draw_rect(start, end, 0);
	return (0);
}
