/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:13:38 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/28 17:46:19 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*find_map_line(t_list *head, char *to_find)
{
	t_list	*ptr;

	ptr = head;
	while (ptr)
	{
		if (ft_strncmp(ptr->content, to_find, ft_strlen(to_find)) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	read_textures(void)
{
	t_game	*game;
	t_map	*map;
	t_list	*raw_line;

	game = get_game_struct();
	map = &(game->map);
	raw_line = find_map_line(game->map.raw, "NO");
	if (raw_line == NULL)
		return (FT_ERROR);
	map->path_north_texture = ft_strdup(raw_line->content + 3);
	raw_line = find_map_line(game->map.raw, "SO");
	if (raw_line == NULL)
		return (FT_ERROR);
	map->path_south_texture = ft_strdup(raw_line->content + 3);
	raw_line = find_map_line(game->map.raw, "WE");
	if (raw_line == NULL)
		return (FT_ERROR);
	map->path_west_texture = ft_strdup(raw_line->content + 3);
	raw_line = find_map_line(game->map.raw, "EA");
	if (raw_line == NULL)
		return (FT_ERROR);
	map->path_east_texture = ft_strdup(raw_line->content + 3);
	return (FT_SUCCESS);
}

static int	check_color_range(int color)
{
	if (color < 0 || color > 255)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

static int	check_map_color_range(char **floor_colors, char **ceiling_colors)
{
	if (check_color_range(ft_atoi(floor_colors[0])) == FT_ERROR ||
		check_color_range(ft_atoi(floor_colors[1])) == FT_ERROR ||
		check_color_range(ft_atoi(floor_colors[2])) == FT_ERROR ||
		check_color_range(ft_atoi(ceiling_colors[0])) == FT_ERROR ||
		check_color_range(ft_atoi(ceiling_colors[1])) == FT_ERROR ||
		check_color_range(ft_atoi(ceiling_colors[2])) == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	read_colors(void)
{
	t_game	*game;
	t_map	*map;
	t_list	*raw_line;
	char	**floor_color_split;
	char	**ceiling_color_split;
	int		floor_color;
	int		ceiling_color;

	game = get_game_struct();
	map = &(game->map);
	raw_line = find_map_line(game->map.raw, "F");
	if (raw_line == NULL)
		return (FT_ERROR);
	floor_color_split = ft_split(raw_line->content + 2, ',');
	if (floor_color_split == NULL || ft_split_length(floor_color_split) != 3)
	{
		ft_split_free(floor_color_split);
		return (FT_ERROR);
	}
	raw_line = find_map_line(game->map.raw, "C");
	if (raw_line == NULL)
		return (FT_ERROR);
	ceiling_color_split = ft_split(raw_line->content + 2, ',');
	if (ceiling_color_split == NULL || ft_split_length(ceiling_color_split) != 3)
	{
		ft_split_free(floor_color_split);
		ft_split_free(ceiling_color_split);
		return (FT_ERROR);
	}
	if (check_map_color_range(floor_color_split, ceiling_color_split) == FT_ERROR)
	{
		ft_split_free(floor_color_split);
		ft_split_free(ceiling_color_split);
		return (FT_ERROR);
	}
	floor_color = (ft_atoi(floor_color_split[0]) << 16) +
					(ft_atoi(floor_color_split[1]) << 8) +
					ft_atoi(floor_color_split[2]);
	ceiling_color = (ft_atoi(ceiling_color_split[0]) << 16) +
					(ft_atoi(ceiling_color_split[1]) << 8) +
					ft_atoi(ceiling_color_split[2]);
	map->floor_color = floor_color;
	map->ceiling_color = ceiling_color;
	ft_split_free(floor_color_split);
	ft_split_free(ceiling_color_split);
	return (FT_SUCCESS);
}

int	parse_map(void)
{
	t_game	*game;

	game = get_game_struct();
	if (game->map.raw == NULL)
		return (FT_ERROR);
	if (read_textures() == FT_ERROR ||
		read_colors() == FT_ERROR ||
		read_map() == FT_ERROR)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
