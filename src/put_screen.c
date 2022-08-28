/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:21:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/28 16:40:57 by cpak             ###   ########seoul.kr  */
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
	else if (wall_dir == WALL_DOOR)
		texture = game->map.textures.door;
	return (texture);
}

static void	put_wall_line(int x, int wall_dir, float wall_dist, float collision_point)
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
	if (y < 0)
	{
		texture_y = (float)(texture->height) / (float)lineHeight * (int)y * -1;
		y -= (int)y;
	}
	while (y < y_end)
	{
		texture_y += (float)(texture->height) / (float)lineHeight;
		y++;
		if (y <= 0)
			continue ;
		if (y >= WINDOW_HEIGHT)
			break ;
		put_image_pixel(game->screen, x, y, get_image_pixel(texture, texture_x, (int)texture_y));
	}
}

int	put_screen_wall(void)
{
	t_game		*game;
	t_player	*player;
	int			w;
	float		cameraX;
	t_dda		dda;

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

		

		put_wall_line(w, dda.wall_dir, dda.wall_dist, dda.wall_collision_point);
		w += 1;
	}
	return (0);
}

int	put_screen_ceiling_floor(void)
{
	t_game		*game;
	t_point		ceiling_start;
	t_point		ceiling_end;
	t_point		floor_start;
	t_point		floor_end;

	game = get_game_struct();
	ceiling_start.x = 0;
	ceiling_start.y = 0;
	ceiling_end.x = WINDOW_WIDTH;
	ceiling_end.y = WINDOW_HEIGHT / 2;
	floor_start.x = 0;
	floor_start.y = WINDOW_HEIGHT / 2;
	floor_end.x = WINDOW_WIDTH;
	floor_end.y = WINDOW_HEIGHT;
	put_image_rect(game->screen, ceiling_start, ceiling_end, game->map.ceiling_color);
	put_image_rect(game->screen, floor_start, floor_end, game->map.floor_color);
	return (FT_SUCCESS);
}
