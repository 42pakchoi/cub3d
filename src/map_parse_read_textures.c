/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_read_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:13:38 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 18:17:49 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
