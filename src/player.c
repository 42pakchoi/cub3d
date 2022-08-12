/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:33:46 by cpak              #+#    #+#             */
/*   Updated: 2022/08/12 18:12:39 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, int angle)
{
	game->player.dir = calc_rotated_vector(game->player.dir, angle);
	game->player.plane = calc_rotated_vector(game->player.plane, angle);
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
				game->player.pos.y = i;
				game->player.pos.x = j;
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

	game = get_game_struct();
	game->player.dir.x = 0;
	game->player.dir.y = -1;
	game->player.plane.x = 1;
	game->player.plane.y = 0;
	set_player_pos();
	if (game->player.character == MAP_PLAYER_E)
		rotate_player(game, 90);
	if (game->player.character == MAP_PLAYER_S)
		rotate_player(game, 180);
	if (game->player.character == MAP_PLAYER_W)
		rotate_player(game, 270);
}
