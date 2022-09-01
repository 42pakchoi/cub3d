/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:20:22 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/01 19:12:37 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_vector	find_player_pos(void)
{
	t_game		*game;
	t_map		*map;
	t_vector	pos;

	game = get_game_struct();
	map = &(game->map);
	pos.y = 0;
	while (pos.y < map->height)
	{
		pos.x = 0;
		while (pos.x < map->width)
		{
			if (is_player_char(map->array[(int)pos.y][(int)pos.x]))
				return (pos);
			pos.x++;
		}
		pos.y++;
	}
	return (pos);
}

static void	flood_wall(char **array, int x, int y)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	if (x < 0 || (int)map->width <= x
		|| y < 0 || (int)map->height <= y
		|| array[y][x] == MAP_OUTSIDE)
	{
		map->is_walled = FT_FALSE;
		return ;
	}
	if (!is_player_char(array[y][x])
		&& array[y][x] != MAP_EMPTY)
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
	size_t	i;
	size_t	j;
	char	**dup;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	dup = (char **)malloc(sizeof(char *) * (map->height + 1));
	dup[map->height] = NULL;
	while (i < map->height)
	{
		dup[i] = (char *)malloc(sizeof(char) * (map->width + 1));
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
	int	i;

	i = 0;
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
	t_game		*game;
	t_map		*map;
	t_vector	start_coord;
	char		**temp_array;

	game = get_game_struct();
	map = &(game->map);
	map->is_walled = FT_TRUE;
	start_coord = find_player_pos();
	temp_array = duplicate_map_array(map->array);
	flood_wall(temp_array, (int)start_coord.x, (int)start_coord.y);

	// print temp_array
	int i = 0;
	while (temp_array[i])
	{
		printf("|%s|\n", temp_array[i]);
		i++;
	}

	free_array(temp_array);
	if (map->is_walled == FT_FALSE)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
