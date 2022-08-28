/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:33:46 by cpak              #+#    #+#             */
/*   Updated: 2022/08/28 09:51:06 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_game *game, int angle)
{
	game->player.dir = calc_rotated_vector(game->player.dir, angle);
	game->player.plane = calc_rotated_vector(game->player.plane, angle);
}

static void	set_player_init_pos(void)
{
	t_game	*game;
	t_map	*map;
	size_t	i;
	size_t	j;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->array[i][j] == MAP_PLAYER_N ||
				map->array[i][j] == MAP_PLAYER_S ||
				map->array[i][j] == MAP_PLAYER_E ||
				map->array[i][j] == MAP_PLAYER_W)
			{
				game->player.character = map->array[i][j];
				game->player.pos.y = i + 0.5;
				game->player.pos.x = j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_player(void)
{
	t_game	*game;

	game = get_game_struct();
	game->player.dir.x = 0;
	game->player.dir.y = -1;
	game->player.plane.x = 0.66;
	game->player.plane.y = 0;
	set_player_init_pos();
	if (game->player.character == MAP_PLAYER_E)
		rotate_player(game, 90);
	if (game->player.character == MAP_PLAYER_S)
		rotate_player(game, 180);
	if (game->player.character == MAP_PLAYER_W)
		rotate_player(game, 270);
}

static int	calc_collision_wall(t_vector pos, t_vector delta)
{
	char		**map;
	t_point		p;
	int 		collision_hoz;
	int 		collision_ver;

	map = get_game_struct()->map.array;
	p.x = (int)(pos.x + delta.x);
	p.y = (int)(pos.y + delta.y);
	collision_hoz = (map[p.y][(int)(pos.x)] == MAP_WALL || map[p.y][(int)(pos.x)] == MAP_DOOR);
	collision_ver = (map[(int)pos.y][p.x] == MAP_WALL || map[(int)pos.y][p.x] == MAP_DOOR);
	if (collision_hoz && collision_ver)
		return (COLLISION_CORNER);
	if (collision_ver)
		return (COLLISION_VER);
	if (collision_hoz)
		return (COLLISION_HOZ);
	return (COLLISION_NONE);
}

void	move_player(t_vector delta)
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

void	set_player(void)
{
	t_game		*game;
	t_vector	delta;

	game = get_game_struct();
	delta.x = 0;
	delta.y = 0;
	if (game->player.key.move[KEY_INDEX_W])
	{
		delta.x += game->player.dir.x * PLAYER_SPEED;
		delta.y += game->player.dir.y * PLAYER_SPEED;
	}
	if (game->player.key.move[KEY_INDEX_S])
	{
		delta.x += game->player.dir.x * PLAYER_SPEED * -1;
		delta.y += game->player.dir.y * PLAYER_SPEED * -1;
	}
	if (game->player.key.move[KEY_INDEX_A])
	{
		delta.x += game->player.plane.x * PLAYER_SPEED * -1;
		delta.y += game->player.plane.y * PLAYER_SPEED * -1;
	}
	if (game->player.key.move[KEY_INDEX_D])
	{
		delta.x += game->player.plane.x * PLAYER_SPEED;
		delta.y += game->player.plane.y * PLAYER_SPEED;
	}
	move_player(delta);
	if (game->player.key.rotate)
		rotate_player(game, game->player.key.rotate);
}
