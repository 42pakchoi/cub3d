/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:21:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/22 15:26:24 by cpak             ###   ########seoul.kr  */
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
	// 텍스쳐 배열에서 픽셀을 가져온다.
	// wall_dir로 가져올 텍스쳐 이미지를 선택
	// collision_point로 텍스쳐의 x값을 구하고,
	// lineHeight로 텍스쳐에서 픽셀을 가져온다.
	// 

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
	if (y_start < 0)
		y_start = 0;
	y_end = lineHeight / 2 + WINDOW_HEIGHT / 2;
	if (y_end >= WINDOW_HEIGHT)
		y_end = WINDOW_HEIGHT - 1;
	
	int		y = y_start;

	while (y <= y_end)
	{
		float	dy = (float)(texture->height) / (float)lineHeight;
		texture_y += dy;
		// int		texY = (int)texture_y & (texture->height - 1);
		// int		idx = (int)(texture_y * (texture->size_line / 4) + texture_x);

		// int	offset = texture->bits_per_pixel / CHAR_BIT;
		int	index = 64 * texture_y + texture_x;


		unsigned int	color = texture->addr[index];

		mlx_pixel_put(game->mlx, game->win, x, y, (int)color);
		y++;
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
		{
			collision_point = dda.player_pos.x + wall_dist * dda.ray_dir.x;
			if (dda.ray_dir.x > 0)
				collision_point = 1 - collision_point;
		}
		else
		{
			collision_point = dda.player_pos.y + wall_dist * dda.ray_dir.y;
			if (dda.ray_dir.y < 0)
				collision_point = 1 - collision_point;
		}
		collision_point -= floor(collision_point);
		draw_wall_line(w, dda.wall_dir, wall_dist, collision_point);
		
		w += 1;
	}

	// int	x = 10;
	// int y = 10;
	// t_img	*texture = game->map.textures.north;

	// while (y < 310)
	// {
	// 	x = 10;
	// 	while (x < 310)
	// 	{
	// 		int idx = (y - 10) * texture->size_line / 4 + (x - 10);
	// 		int color = texture->addr[idx];
			
	// 		mlx_pixel_put(game->mlx, game->win, x, y, color);
	// 		x += 1;
	// 	}
	// 	y += 1;
	// }


	return (0);
}



