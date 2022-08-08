/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:10:28 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 15:28:02 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_minimap_tiles()
{
	t_game	*game;
	t_map	*map;
	size_t	i;
	size_t	j;
	t_vector	start;
	t_vector	end;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			start.x = j * MINIMAP_TILE_SIZE;
			start.y = i * MINIMAP_TILE_SIZE;
			end.x = j * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE;
			end.y = i * MINIMAP_TILE_SIZE + MINIMAP_TILE_SIZE;
			if (map->array[i][j] == '1')
				draw_rect(start, end, MINIMAP_WALL_COLOR);
			j++;
		}
		i++;
	}
}

void	put_minimap(void)
{
	t_game	*game;
	t_map	*map;
	t_vector	start;
	t_vector	end;

	game = get_game_struct();
	map = &(game->map);
	start.x = 0;
	start.y = 0;
	end.x = map->width * MINIMAP_TILE_SIZE;
	end.y = map->height * MINIMAP_TILE_SIZE;
	draw_rect(start, end, MINIMAP_FLOOR_COLOR);
	// mlx_put_image_to_window(game->mlx, game->win, map->textures.minimap_floor->img_ptr, 0, 0);
	put_minimap_tiles();
}

// void	draw_frame(void)
// {
// 	t_game	*game;

// 	game = get_game_struct();
// 	mlx_clear_window(game->mlx, game->win);
// 	put_minimap();
// }
