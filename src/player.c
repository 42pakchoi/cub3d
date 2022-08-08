/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:33:46 by cpak              #+#    #+#             */
/*   Updated: 2022/08/08 17:39:17 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, int angle)
{
	game->player.dir = calc_rotated_vector(game->player.dir, angle);
	game->player.fov.start = calc_rotated_vector(game->player.fov.start, angle);
	game->player.fov.end = calc_rotated_vector(game->player.fov.end, angle);
	int	i = 0;
	while (i <= 20)
	{
		game->player.rays[i] = calc_rotated_vector(game->player.rays[i], angle);
		i += 1;
	}
}

void	set_player_pos(void)
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
				game->player.grid_pos.x = j;
				game->player.grid_pos.y = i;
				game->player.pos.x = j * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2;
				game->player.pos.y = i * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE / 2;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	prepare_player(void)
{
	t_game	*game;
	int	val = -20;
	int i = 0;

	game = get_game_struct();
	game->player.dir.x = 0;
	game->player.dir.y = -30;
	game->player.fov.start.x = -20;
	game->player.fov.start.y = -30;
	game->player.fov.end.x = 20;
	game->player.fov.end.y = -30;
	while (val <= 20)
	{
		game->player.rays[i].x = val;
		game->player.rays[i].y = -30;
		val += 2;
		i += 1;
	}
	set_player_pos();
	if (game->player.character == MAP_PLAYER_E)
		rotate_player(game, 90);
	if (game->player.character == MAP_PLAYER_S)
		rotate_player(game, 180);
	if (game->player.character == MAP_PLAYER_W)
		rotate_player(game, 270);
}
