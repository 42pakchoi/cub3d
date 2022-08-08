/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:20:22 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 01:24:11 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vector	find_left_top_empty()
{
	t_game	*game;
	t_map	*map;
	t_vector	left_top_empty;

	game = get_game_struct();
	map = &(game->map);
	left_top_empty.y = 0;
	while (left_top_empty.y < map->height)
	{
		left_top_empty.x = 0;
		while (left_top_empty.x < map->width)
		{
			if (map->array[(int)left_top_empty.y][(int)left_top_empty.x] == MAP_EMPTY)
				return (left_top_empty);
			left_top_empty.x++;
		}
		left_top_empty.y++;
	}
	return (left_top_empty);
}

static void	flood_wall(char **array, int x, int y)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	if (x < 0 || (int)map->width <= x || y < 0 || (int)map->height <= y ||
		array[y][x] == MAP_OUTSIDE)
	{
		map->is_walled = FT_FALSE;
		return ;
	}
	if (array[y][x] != MAP_EMPTY)
		return ;
	array[y][x] = MAP_TEST_VISITED;
	flood_wall(array, x + 1, y);
	flood_wall(array, x - 1, y);
	flood_wall(array, x, y + 1);
	flood_wall(array, x, y - 1);
}

static char	**duplicate_map_array(char **orig)
{
	t_game	*game;
	t_map	*map;
	size_t i;
	size_t j;
	char **dup;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	dup = (char**)malloc(sizeof(char*) * map->height + 1);
	dup[map->height] = NULL;
	while (i < map->height)
	{
		dup[i] = (char*)malloc(sizeof(char) * map->width + 1);
		dup[i][map->width] = '\0';
		j = 0;
		while (j < map->width)
		{
			dup[i][j] = orig[i][j];
			j++;
		}
		i++;
	}
	return (dup);
}

static char	**free_array(char **array)
{
	int i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

int	check_map_walls(void)
{
	t_game	*game;
	t_map	*map;
	t_vector	start_coord;
	char	**temp_array;

	game = get_game_struct();
	map = &(game->map);
	map->is_walled = FT_TRUE;
	start_coord = find_left_top_empty();
	temp_array = duplicate_map_array(map->array);
	printf("<TEST> start_coord: %f, %f\n", start_coord.x, start_coord.y);
	flood_wall(temp_array, (int)start_coord.x, (int)start_coord.y);

	// TEST
	size_t		i;
	i = 0;
	printf("<TEST> 'temp_array'\n");
	while (temp_array[i])
	{
		printf("|%s|\n", temp_array[i]);
		i++;
	}
	// TEST

	free_array(temp_array);
	if (map->is_walled == FT_FALSE)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
