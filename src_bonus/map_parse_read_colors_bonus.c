/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_read_colors_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:13:38 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_color_range(int color)
{
	if (color < 0 || color > 255)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

static int	check_map_color_range(char **color_split)
{
	if (
		check_color_range(ft_atoi(color_split[0])) == FT_ERROR
		|| check_color_range(ft_atoi(color_split[1])) == FT_ERROR
		|| check_color_range(ft_atoi(color_split[2])) == FT_ERROR
	)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

static int	get_hex_color(char **three_color_split)
{
	int	color;

	color = 0;
	color += ft_atoi(three_color_split[0]) << 16;
	color += ft_atoi(three_color_split[1]) << 8;
	color += ft_atoi(three_color_split[2]);
	return (color);
}

/*
** @param c: 'F' or 'C'('F' for floor color, 'C' for ceiling color)
** @return color in hex
*/
static int	get_color(char *c)
{
	t_game	*game;
	t_list	*raw_line;
	char	**color_split;
	int		color;

	game = get_game_struct();
	raw_line = find_map_line(game->map.raw, c);
	if (raw_line == NULL)
		return (FT_ERROR);
	color_split = ft_split(raw_line->content + 2, ',');
	if (color_split == NULL || ft_split_length(color_split) != 3)
	{
		ft_split_free(color_split);
		return (FT_ERROR);
	}
	if (check_map_color_range(color_split) == FT_ERROR)
	{
		ft_split_free(color_split);
		return (FT_ERROR);
	}
	color = get_hex_color(color_split);
	ft_split_free(color_split);
	return (color);
}

int	read_colors(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	map->floor_color = get_color("F");
	map->ceiling_color = get_color("C");
	return (FT_SUCCESS);
}
