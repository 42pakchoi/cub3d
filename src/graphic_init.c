/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:53:01 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/22 17:08:37 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img *make_mlx_image_minimap(int width, int height)
{
	t_game *game;
	t_img * image;

	game = get_game_struct();
	image = (t_img *) malloc(sizeof(t_img));
	image->img_ptr = mlx_new_image(game->mlx, width, height);
	if (!image->img_ptr)
		return (NULL);
	image->addr = (int *) mlx_get_data_addr(
	    image->img_ptr, &(image->bits_per_pixel), &(image->size_line), &(image->endian));
	image->width = width;
	image->height = height;
	game->map.textures.minimap_floor = image;
	return (image);
}

static void set_minimap_images(void)
{
	t_game *game;
	t_map * map;

	game = get_game_struct();
	map = &(game->map);
	map->textures.minimap_floor =
		make_mlx_image_minimap((int) map->width * MINIMAP_TILE_SIZE, (int) map->height * MINIMAP_TILE_SIZE);
}

static void	set_texture_images(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	map->textures.south = get_png_image(map->path_south_texture);
	map->textures.north = get_png_image(map->path_north_texture);
	map->textures.west = get_png_image(map->path_west_texture);
	map->textures.east = get_png_image(map->path_east_texture);
	if (map->textures.south == NULL || map->textures.north == NULL || 
		map->textures.west == NULL || map->textures.east == NULL)
	{
		// 이미지 처리에 문제가 발생한 경우
		printf("error\n");
		return ;
	}
}

void	init_images(void)
{
	set_texture_images();
	set_minimap_images();
	put_minimap_floor();
	put_minimap_tiles();
	put_minimap_ray();
	put_minimap_player();
}
