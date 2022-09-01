/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:33:46 by cpak              #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	calc_collision_wall(t_vector pos, t_vector delta)
{
	char	**map;
	t_point	p;
	int		collision_hoz;
	int		collision_ver;

	map = get_game_struct()->map.array;
	p.x = (int)(pos.x + delta.x);
	p.y = (int)(pos.y + delta.y);
	collision_hoz = (map[p.y][(int)(pos.x)] == MAP_WALL
			|| map[p.y][(int)(pos.x)] == MAP_DOOR
			|| map[p.y][(int)(pos.x)] == MAP_WALL_FIRE);
	collision_ver = (map[(int)pos.y][p.x] == MAP_WALL
			|| map[(int)pos.y][p.x] == MAP_DOOR
			|| map[(int)pos.y][p.x] == MAP_WALL_FIRE);
	if (collision_hoz && collision_ver)
		return (COLLISION_CORNER);
	if (collision_ver)
		return (COLLISION_VER);
	if (collision_hoz)
		return (COLLISION_HOZ);
	return (COLLISION_NONE);
}

static void	move_player(t_vector delta)
{
	t_game	*game;
	int		wall;

	game = get_game_struct();
	if (delta.x != 0 || delta.y != 0)
	{
		wall = calc_collision_wall(game->player.pos, delta);
		if (wall == COLLISION_NONE)
		{
			game->player.pos.x += delta.x;
			game->player.pos.y += delta.y;
		}
		else if (wall == COLLISION_HOZ)
			game->player.pos.x += delta.x;
		else if (wall == COLLISION_VER)
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
	set_delta(&delta, game->player.key.move,
		game->player.dir, game->player.plane
		);
	move_player(delta);
	if (game->player.key.rotate)
		rotate_player(game, game->player.key.rotate);
}
