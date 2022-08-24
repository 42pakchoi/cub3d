/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:21:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/24 13:16:53 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*get_texture_img(int wall_dir)
{
	t_game	*game;
	t_img	*texture;

	texture = NULL;
	game = get_game_struct();
	if (wall_dir == WALL_DIR_N)
		texture = game->map.textures.north;
	else if (wall_dir == WALL_DIR_S)
		texture = game->map.textures.south;
	else if (wall_dir == WALL_DIR_E)
		texture = game->map.textures.east;
	else if (wall_dir == WALL_DIR_W)
		texture = game->map.textures.west;
	return (texture);
}

static void	draw_wall_line(int x, int wall_dir, float wall_dist, float collision_point)
{
	t_game	*game;
	t_img	*texture;

	int		texture_x;
	float	texture_y;
	float	lineHeight;

	float	y_end;
	float	y;

	game = get_game_struct();
	texture = get_texture_img(wall_dir);

	texture_x = (int)((float)(texture->width) * collision_point);
	texture_y = 0;

	lineHeight = ((float)WINDOW_HEIGHT / wall_dist);
	y_end = lineHeight / 2 + WINDOW_HEIGHT / 2 - 1;
	if (y_end >= WINDOW_HEIGHT)
		y_end = WINDOW_HEIGHT - 1;
	y = -lineHeight / 2 + WINDOW_HEIGHT / 2;
	while (y < y_end)
	{
		texture_y += (float)(texture->height) / (float)lineHeight;
		y++;
		if (y <= 0)
			continue ;
		if (y >= WINDOW_HEIGHT)
			break ;
		mlx_pixel_put(
			game->mlx, game->win, x, y, 
			get_image_pixel(texture, texture_x, texture_y)
			);
	}
}

int	draw_wall(void)
{
	t_game		*game;
	t_player	*player;
	int			w;
	float		cameraX;
	t_dda		dda;
	float		wall_dist;

	game = get_game_struct();
	player = &(game->player);
	dda.player_pos = player->pos;
	dda.player_pos = player->pos;
	w = 0;
	while (w < WINDOW_WIDTH)
	{
		cameraX = 2 * w / (float)WINDOW_WIDTH - 1;
		dda.ray_dir.x = player->dir.x + player->plane.x * cameraX;
		dda.ray_dir.y = player->dir.y + player->plane.y * cameraX;
		init_dda(&dda);
		calc_collision_point(game->map.array, &dda);
		wall_dist = get_perpendicular_wall_dist(dda.player_pos, dda.ray_dir, &dda);

		float collision_point;
		if (dda.wall_dir == WALL_DIR_N || dda.wall_dir == WALL_DIR_S)
			collision_point = dda.player_pos.x + wall_dist * dda.ray_dir.x;
		else
			collision_point = dda.player_pos.y + wall_dist * dda.ray_dir.y;
		collision_point -= floor(collision_point);
		draw_wall_line(w, dda.wall_dir, wall_dist, collision_point);
		w += 1;
	}
	return (0);
}



