/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:21:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/22 16:57:39 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_wall_color(int wall_dir)
{
	if (wall_dir == 0)
		return (0x0000FF);
	else if (wall_dir == 1)
		return (0xFFFF00);
	else if (wall_dir == 2)
		return (0x00FF00);
	else if (wall_dir == 3)
		return (0xFF0000);
	else
		return (0x00FF00);
}

void	draw_screen_line(int x, float wall_dist, int color)
{
	t_game	*game;
	int lineHeight;
	int y_start;
	int y_end;
	int y;

	game = get_game_struct();
	lineHeight = (int)(WINDOW_HEIGHT / wall_dist);
	y_start = -lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (y_start < 0)
		y_start = 0;
	y_end = lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (y_end >= WINDOW_HEIGHT)
		y_end = WINDOW_HEIGHT - 1;
	y = y_start;
	while (y <= y_end)
	{
		mlx_pixel_put(game->mlx, game->win, x, y, color);
		y++;
	}
}

static void	draw_wall_line(int x, int wall_dir, float wall_dist, float collision_point)
{
	t_game	*game;
	t_img	*texture = NULL;

	game = get_game_struct();

	if (wall_dir == WALL_DIR_N)
		texture = game->map.textures.north;
	else if (wall_dir == WALL_DIR_S)
		texture = game->map.textures.south;
	else if (wall_dir == WALL_DIR_E)
		texture = game->map.textures.east;
	else if (wall_dir == WALL_DIR_W)
		texture = game->map.textures.west;

	int		texture_x;
	float	texture_y;
	int		lineHeight;

	int		y_start;
	int		y_end;

	texture_x = (int)((float)(texture->width) * collision_point);
	texture_y = 0;

	lineHeight = (int)(WINDOW_HEIGHT / wall_dist);
	y_start = -lineHeight / 2 + WINDOW_HEIGHT / 2;
	y_end = lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (y_end >= WINDOW_HEIGHT)
		y_end = WINDOW_HEIGHT - 1;
	
	int		y = y_start;

	while (y <= y_end)
	{
		
		float	dy = (float)(texture->height) / (float)lineHeight;
		int		offset = (texture->size_line - (texture->width * 4)) / 4;
		
		texture_y += dy;


		int		index = (texture->width + offset) * (int)texture_y + texture_x;
		int		color = texture->addr[index];

		y++;
		if (y <= 0)
			continue ;
		if (y >= WINDOW_HEIGHT)
			break ;
		mlx_pixel_put(game->mlx, game->win, x, y, (int)color);
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



