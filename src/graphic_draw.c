/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:10:28 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 02:45:44 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_minimap_tiles()
{
	t_game	*game;
	t_map	*map;
	size_t	i;
	size_t	j;

	game = get_game_struct();
	map = &(game->map);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->array[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win,
					map->textures.minimap_wall->img_ptr,
					j * MINIMAP_TILE_SIZE, i * MINIMAP_TILE_SIZE);
			j++;
		}
		i++;
	}
}

static void	put_minimap(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	mlx_put_image_to_window(game->mlx, game->win, map->textures.minimap_floor->img_ptr, 0, 0);
	put_minimap_tiles();
}

void	draw_frame(void)
{
	t_game	*game;

	game = get_game_struct();
	mlx_clear_window(game->mlx, game->win);
	put_minimap();
}
