/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:33:46 by cpak              #+#    #+#             */
/*   Updated: 2022/08/31 14:32:33 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_player(t_vector delta)
{
	t_game	*game;
	float	x;
	float	y;

	game = get_game_struct();
	if (delta.x != 0 || delta.y != 0)
	{
		x = game->player.pos.x + delta.x;
		y = game->player.pos.y + delta.y;
		if (x < 0 || x >= game->map.width)
			return ;
		if (y < 0 || y >= game->map.height)
			return ;
		game->player.pos.x += delta.x;
		game->player.pos.y += delta.y;
	}
}

static void	set_delta(
	t_vector *delta, int move[4], t_vector dir, t_vector plane
	)
{
	if (move[KEY_INDEX_W])
	{
		delta->x += dir.x * PLAYER_SPEED;
		delta->y += dir.y * PLAYER_SPEED;
	}
	if (move[KEY_INDEX_S])
	{
		delta->x += dir.x * PLAYER_SPEED * -1;
		delta->y += dir.y * PLAYER_SPEED * -1;
	}
	if (move[KEY_INDEX_A])
	{
		delta->x += plane.x * PLAYER_SPEED * -1;
		delta->y += plane.y * PLAYER_SPEED * -1;
	}
	if (move[KEY_INDEX_D])
	{
		delta->x += plane.x * PLAYER_SPEED;
		delta->y += plane.y * PLAYER_SPEED;
	}
}

void	set_player(void)
{
	t_game		*game;
	t_vector	delta;

	game = get_game_struct();
	delta.x = 0;
	delta.y = 0;
	set_delta(&delta,
		game->player.key.move,
		game->player.dir,
		game->player.plane);
	move_player(delta);
	if (game->player.key.rotate)
		rotate_player(game, game->player.key.rotate);
}
