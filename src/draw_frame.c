/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/16 16:29:09 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_frame()
{
	t_game	*game;

	game = get_game_struct();
	mlx_clear_window(game->mlx, game->win);
	erase_minimap_dirline();
	erase_minimap_fov();
	erase_minimap_ray();
	erase_minimap_player();
}

void draw_minimap(void)
{
	draw_minimap_wall();
	draw_minimap_ray();
	draw_minimap_dirline();
	draw_minimap_fov();
	draw_minimap_player();
}

void	set_player(void)
{
	t_game		*game;
	t_vector	dir;
	t_vector	plane;

	game = get_game_struct();
	dir = game->player.dir;
	plane = game->player.plane;

	dir.x /= 5;
	dir.y /= 5;
	plane.x /= 5;
	plane.y /= 5;

	if (game->player.key.move[0])
	{
		game->player.pos.x += dir.x;
		game->player.pos.y += dir.y;
	}
	if (game->player.key.move[1])
	{
		game->player.pos.x -= dir.x;
		game->player.pos.y -= dir.y;
	}
	if (game->player.key.move[2])
	{
		game->player.pos.x -= plane.x;
		game->player.pos.y -= plane.y;
	}
	if (game->player.key.move[3])
	{
		game->player.pos.x += plane.x;
		game->player.pos.y += plane.y;
	}
	if (game->player.key.rotate)
		rotate_player(game, game->player.key.rotate);
}

int	draw_frame(void)
{
	clear_frame();
	set_player();
	draw_wall();
	draw_minimap();
	return (0);
}
