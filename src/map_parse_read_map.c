/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_read_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:21:02 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 19:04:26 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	get_map_height(t_list *map_start_line)
{
	size_t	height;

	height = 0;
	while (map_start_line)
	{
		if (ft_strlen(map_start_line->content) == 0)
			break ;
		height++;
		map_start_line = map_start_line->next;
	}
	return (height);
}

static size_t	get_map_width(t_list *map_start_line)
{
	size_t	width;
	size_t	temp_width;

	width = 0;
	while (map_start_line)
	{
		temp_width = ft_strlen(map_start_line->content);
		if (width < temp_width)
			width = temp_width;
		map_start_line = map_start_line->next;
	}
	return (width);
}

static int	make_list_to_array(void)
{
	t_game	*game;
	t_map	*map;
	t_list	*raw_p;

	game = get_game_struct();
	map = &(game->map);
	raw_p = find_map_start_line();
	if (raw_p == NULL)
		return (FT_ERROR);
	map->height = get_map_height(raw_p);
	map->width = get_map_width(raw_p);
	map->array = get_map_array(raw_p, map->height, map->width);
	if (map->array == NULL)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	read_map(void)
{
	if (make_list_to_array() == FT_ERROR)
		return (FT_ERROR);
	if (validate_map() == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
