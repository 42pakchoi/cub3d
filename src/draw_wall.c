/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:21:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/17 15:56:47 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_wall_color(int is_horizontal, t_vector ray_dir)
{
	if (is_horizontal == 0 && ray_dir.x > 0)
		return (0xFF0000);
	else if (is_horizontal == 0 && ray_dir.x < 0)
		return (0x00FF00);
	else if (is_horizontal == 1 && ray_dir.y > 0)
		return (0x0000FF);
	else if (is_horizontal == 1 && ray_dir.y < 0)
		return (0xFFFF00);
	else
		return (0x00FF00);
}

static void	draw_screen_line(int x, float wall_dist, int color)
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
		draw_screen_line(w, wall_dist, get_wall_color(dda.is_hoz, dda.ray_dir));
		w += 1;
	}
	return (0);
}
