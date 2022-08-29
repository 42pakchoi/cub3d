/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:16:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 18:17:49 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_char(char c)
{
	if (c == MAP_PLAYER_N
		|| c == MAP_PLAYER_S
		|| c == MAP_PLAYER_E
		|| c == MAP_PLAYER_W
		|| c == MAP_EMPTY
		|| c == MAP_WALL
		|| c == MAP_OUTSIDE
		|| c == MAP_DOOR)
		return (FT_TRUE);
	return (FT_FALSE);
}

int	check_map_characters(void)
{
	t_game	*game;
	t_map	*map;
	size_t	i;
	size_t	j;
	char	temp;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			temp = map->array[i][j];
			if (is_map_char(temp) == FT_FALSE)
				return (FT_FALSE);
			j++;
		}
		i++;
	}
	return (FT_SUCCESS);
}

static int	is_player_char(char c)
{
	if (c == MAP_PLAYER_N
		|| c == MAP_PLAYER_S
		|| c == MAP_PLAYER_W
		|| c == MAP_PLAYER_E)
		return (FT_TRUE);
	return (FT_FALSE);
}

int	check_map_required_characters(void)
{
	t_game	*game;
	t_map	*map;
	size_t	i;
	size_t	j;
	int		count_player;

	game = get_game_struct();
	map = &(game->map);
	count_player = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_player_char(map->array[i][j]))
				count_player++;
			j++;
		}
		i++;
	}
	if (count_player != 1)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
