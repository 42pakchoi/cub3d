/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:16:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/30 19:18:16 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_door(t_map *map, int i, int j)
{
	if (map->array[i - 1][j] == MAP_WALL && map->array[i + 1][j] == MAP_WALL)
		return (!(map->array[i][j - 1] == MAP_WALL
			|| map->array[i][j + 1] == MAP_WALL));
	if (map->array[i][j - 1] == MAP_WALL && map->array[i][j + 1] == MAP_WALL)
		return (!(map->array[i - 1][j] == MAP_WALL
			|| map->array[i + 1][j] == MAP_WALL));
	return (0);
}

static int	check_map_doors(void)
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
			if (temp == MAP_DOOR && is_valid_door(map, i, j) == 0)
				return (FT_ERROR);
			j++;
		}
		i++;
	}
	return (FT_SUCCESS);
}

int	validate_map(void)
{
	if (check_map_characters() == FT_ERROR)
	{
		print_error("Invalid map characters");
		return (FT_ERROR);
	}
	if (check_map_walls() == FT_ERROR)
	{
		print_error("Invalid map walls");
		return (FT_ERROR);
	}
	if (check_map_doors() == FT_ERROR)
	{
		print_error("Invalid map doors");
		return (FT_ERROR);
	}
	if (check_map_required_characters() == FT_ERROR)
	{
		print_error("Invalid map required characters");
		return (FT_ERROR);
	}
	return (FT_SUCCESS);
}
