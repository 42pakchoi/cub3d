/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:33:46 by cpak              #+#    #+#             */
/*   Updated: 2022/08/17 15:45:38 by cpak             ###   ########seoul.kr  */
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
				game->player.pos.y = i;
				game->player.pos.x = j;
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

t_bool	calc_player_collision(t_vector pos)
{
	t_game	*game;
	t_point	p;

	game = get_game_struct();
	p.x = (int)pos.x;
	p.y = (int)pos.y;
	return (game->map.array[p.y][p.x] == MAP_WALL);
}

void	set_player(void)
{
	t_game		*game;
	t_vector	pos;

	game = get_game_struct();
	pos.x = 0;
	pos.y = 0;
	if (game->player.key.move[0])
	{
		pos.x = game->player.pos.x + game->player.dir.x / 5;
		pos.y = game->player.pos.y + game->player.dir.y / 5;
	}
	if (game->player.key.move[1])
	{
		pos.x = game->player.pos.x - game->player.dir.x / 5;
		pos.y = game->player.pos.y - game->player.dir.y / 5;
	}
	if (game->player.key.move[2])
	{
		pos.x = game->player.pos.x - game->player.plane.x / 5;
		pos.y = game->player.pos.y - game->player.plane.y / 5;
	}
	if (game->player.key.move[3])
	{
		pos.x = game->player.pos.x + game->player.plane.x / 5;
		pos.y = game->player.pos.y + game->player.plane.y / 5;
	}
	if (game->player.key.rotate)
		rotate_player(game, game->player.key.rotate);
	if (pos.x != 0 && pos.y != 0 && calc_player_collision(pos) == FT_FALSE)
		game->player.pos = pos;
}
