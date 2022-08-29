/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:53:01 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 15:25:31 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void set_images(void)
{
	t_game *game;
	t_map * map;

	game = get_game_struct();
	map = &(game->map);
	game->minimap = make_mlx_image(
		(int)map->width * map->minimap_tile_size,
		(int)map->height * map->minimap_tile_size
	);
	game->screen = make_mlx_image(WINDOW_WIDTH, WINDOW_HEIGHT);
}

char	*get_fire_image(int i)
{
	char *tmp;
	char *result;

	tmp = ft_itoa(i);
	result = ft_strjoin("./textures/fireplace/fire-", tmp);
	tmp = result;
	result = ft_strjoin(tmp, ".png");
	return (result);
}

static int	set_fire_texture(void)
{
	t_game	*game;
	t_map	*map;
	int 	i;
	char	*path;

	game = get_game_struct();
	map = &(game->map);
	map->textures.fire = (t_img **)malloc(sizeof(t_img *) * 20);
	if (!map->textures.fire)
		return (0);
	map->textures.fire[20] = 0;
	i = 0;
	while (i < 19)
	{
		path = get_fire_image(i);
		map->textures.fire[i] = get_png_image(path);
		if (map->textures.fire[i] == NULL)
			return (0);
		i += 1;
	}
	return (1);
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
	map->textures.door = get_png_image("./textures/door.png");
	map->textures.door_side = get_png_image("./textures/door_side.png");
	if (map->textures.south == NULL || map->textures.north == NULL ||
		map->textures.west == NULL || map->textures.east == NULL ||
		!set_fire_texture())
	{
		// 이미지 처리에 문제가 발생한 경우
		exit_with_error("Failed to load textures");
	}
}

static void calc_minimap()
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	if (MAX_MINIMAP_SIZE < (int)map->width * MINIMAP_TILE_SIZE)
		map->minimap_tile_size = MAX_MINIMAP_SIZE / (int)map->width;
	if (MAX_MINIMAP_SIZE < (int)map->height * MINIMAP_TILE_SIZE)
		map->minimap_tile_size = MAX_MINIMAP_SIZE / (int)map->height;
	else
		map->minimap_tile_size = MINIMAP_TILE_SIZE;
	if (map->minimap_tile_size < 1)
		map->minimap_tile_size = 1;
}

void	init_images(void)
{
	set_texture_images();
	calc_minimap();
	set_images();
}
