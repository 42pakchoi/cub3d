/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:16:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/28 16:05:53 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_characters(void)
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
			if (temp != MAP_PLAYER_N &&
				temp != MAP_PLAYER_S &&
				temp != MAP_PLAYER_E &&
				temp != MAP_PLAYER_W &&
				temp != MAP_EMPTY &&
				temp != MAP_WALL &&
				temp != MAP_OUTSIDE &&
				temp != MAP_DOOR
				)
				return (FT_ERROR);
			j++;
		}
		i++;
	}
	return (FT_SUCCESS);
}

static int	check_map_required_characters()
{
	t_game	*game;
	t_map	*map;
	size_t	i;
	size_t	j;
	char	temp;
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
			temp = map->array[i][j];
			if (temp == MAP_PLAYER_N ||
				temp == MAP_PLAYER_S ||
				temp == MAP_PLAYER_E ||
				temp == MAP_PLAYER_W)
				count_player++;
			j++;
		}
		i++;
	}
	printf("<TEST> count_player: %d\n", count_player);
	if (count_player != 1)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	validate_map(void)
{
	if (check_map_characters() == FT_ERROR)
	{
		printf("<TEST> check_map_characters\n");
		return (FT_ERROR);
	}
	if (check_map_walls() == FT_ERROR)
	{
		printf("<TEST> check_map_walls\n");
		return (FT_ERROR);
	}
	if (check_map_required_characters() == FT_ERROR)
	{
		printf("<TEST> check_map_required_characters\n");
		return (FT_ERROR);
	}
	return (FT_SUCCESS);
}
