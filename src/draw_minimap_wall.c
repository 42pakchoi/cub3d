/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:10:28 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/17 15:14:55 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_floar()
{
	t_game	*game;
	t_point	top_left;

	game = get_game_struct();
	top_left.x = 0;
	top_left.y = 0;
	put_image(game->map.textures.minimap_floor->img_ptr, &top_left);
}

static void	draw_minimap_tiles()
{
	t_game	*game;
	t_map	*map;
	size_t	i;
	size_t	j;
	t_point		wall_point;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			wall_point.x = j * MINIMAP_TILE_SIZE;
			wall_point.y = i * MINIMAP_TILE_SIZE;
			if (map->array[i][j] == '1')
			{
				put_image(map->textures.minimap_wall->img_ptr, &wall_point);
			}
			j++;
		}
		i++;
	}
}

void	draw_minimap_wall(void)
{
	draw_minimap_floar();
	draw_minimap_tiles();
}
