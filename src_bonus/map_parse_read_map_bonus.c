/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_read_map_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:21:02 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static size_t	get_map_height(t_list *map_start_line)
{
	size_t	height;
	size_t	i;
	t_list	*tmp;

	height = 0;
	tmp = map_start_line;
	while (map_start_line)
	{
		height++;
		if (map_start_line->next == NULL)
			break ;
		map_start_line = map_start_line->next;
	}
	i = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->content) == 0)
			i++;
		else
			i = 0;
		tmp = tmp->next;
	}
	return (height - i);
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
