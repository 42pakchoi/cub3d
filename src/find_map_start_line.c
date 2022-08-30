/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_map_start_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:47:25 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 18:17:37 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_type(char *content)
{
	if (ft_strncmp(content, "NO", 2) == 0
		|| ft_strncmp(content, "SO", 2) == 0
		|| ft_strncmp(content, "WE", 2) == 0
		|| ft_strncmp(content, "EA", 2) == 0
		|| ft_strncmp(content, "S", 1) == 0
		|| ft_strncmp(content, "F", 1) == 0
		|| ft_strncmp(content, "C", 1) == 0)
		return (FT_TRUE);
	return (FT_FALSE);
}

t_list	*find_map_start_line(void)
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
		if (is_map_type(raw_line->content))
			count_type_id++;
		raw_line = raw_line->next;
		if (count_type_id == 6)
			break ;
	}
	while (raw_line && ft_strlen(raw_line->content) == 0)
		raw_line = raw_line->next;
	return (raw_line);
}
