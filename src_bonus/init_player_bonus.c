/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:38:20 by cpak              #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotate_player(t_game *game, int angle)
{
	game->player.dir = calc_rotated_vector(game->player.dir, angle);
	game->player.plane = calc_rotated_vector(game->player.plane, angle);
}

static int	is_player(char c)
{
	return (c == MAP_PLAYER_N
		|| c == MAP_PLAYER_S
		|| c == MAP_PLAYER_E
		|| c == MAP_PLAYER_W
	);
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
			if (is_player(map->array[i][j]))
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
