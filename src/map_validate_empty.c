/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_empty.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 21:58:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/30 21:58:52 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != MAP_OUTSIDE)
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

int	check_map_empty_line(void)
{
	t_game	*game;
	t_map	*map;
	size_t	i;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	while (i < map->height)
	{
		if (is_empty_line(map->array[i]) == FT_TRUE)
			return (FT_ERROR);
		i++;
	}
	return (FT_SUCCESS);
}
