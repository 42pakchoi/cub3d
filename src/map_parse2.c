/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:21:02 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 01:26:23 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*find_map_start_line()
{
	t_game	*game;
	t_map	*map;
	t_list	*raw_line;
	int		count_type_id;

	game = get_game_struct();
	map = &(game->map);
	raw_line = map->raw;
	count_type_id = 0;
	while (raw_line)
	{
		if (ft_strncmp(raw_line->content, "NO", 2) == 0 ||
			ft_strncmp(raw_line->content, "SO", 2) == 0 ||
			ft_strncmp(raw_line->content, "WE", 2) == 0 ||
			ft_strncmp(raw_line->content, "EA", 2) == 0 ||
			ft_strncmp(raw_line->content, "S", 1) == 0 ||
			ft_strncmp(raw_line->content, "F", 1) == 0 ||
			ft_strncmp(raw_line->content, "C", 1) == 0
		)
			count_type_id++;
		raw_line = raw_line->next;
		if (count_type_id == 6)
			break;
	}
	while (raw_line && ft_strlen(raw_line->content) == 0)
		raw_line = raw_line->next;
	return (raw_line);
}

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
	size_t		i;
	size_t		j;

	game = get_game_struct();
	map = &(game->map);
	raw_p = find_map_start_line();
	if (raw_p == NULL)
		return (FT_ERROR);
	map->height = get_map_height(raw_p);
	map->width = get_map_width(raw_p);
	map->array = (char **)malloc(sizeof(char *) * map->height + 1);
	map->array[map->height] = NULL;
	i = 0;
	while (i < map->height)
	{
		map->array[i] = malloc(sizeof(char) * map->width + 1);
		map->array[i][map->width] = '\0';
		j = 0;
		while (j < map->width)
		{
			if (ft_strlen(raw_p->content) > (int)j)
				map->array[i][j] = *(char *)(raw_p->content + j);
			else
				map->array[i][j] = MAP_OUTSIDE;
			j++;
		}
		i++;
		raw_p = raw_p->next;
	}
	return (FT_SUCCESS);
}

static void	test_print_array_map(void)
{
	t_game	*game;
	t_map	*map;
	size_t		i;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	printf("<TEST> array map\n");
	while (i < map->height)
	{
		printf("|%s|\n", map->array[i]);
		i++;
	}
}

int	read_map(void)
{
	if (make_list_to_array() == FT_ERROR)
		return (FT_ERROR);
	test_print_array_map();
	if (validate_map() == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
