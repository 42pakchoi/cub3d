/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/29 22:59:00 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	draw_sprite(t_img *sprite, float wall_dist, int x, int dy)
// {
// 	t_game	*game;

// 	game = get_game_struct();
// 	float	texture_y = 0;
// 	float	lineHeight = ((float)WINDOW_HEIGHT / wall_dist);
// 	float	y_end;
// 	float	y;

// 	y_end = lineHeight / 2 + WINDOW_HEIGHT / 2 - 1;
// 	if (y_end >= WINDOW_HEIGHT)
// 		y_end = WINDOW_HEIGHT - 1;
// 	y = -lineHeight / 2 + WINDOW_HEIGHT / 2;
// 	if (y < 0)
// 	{
// 		texture_y = (float)(100) / (float)lineHeight * (int)y * -1 + dy;
// 		y -= (int)y;
// 	}
// 	while (y < y_end)
// 	{
// 		texture_y += (float)(100) / (float)lineHeight + dy;
// 		y++;
// 		if (y <= 0)
// 			continue ;
// 		if (y >= WINDOW_HEIGHT)
// 			break ;
// 		put_image_pixel(game->screen, x, y, get_image_pixel(sprite, (int)texture_y, (int)texture_y));
// 	}
// }

// void	put_sprite(void)
// {
// 	t_game	*game;
// 	t_img	*sprite;

// 	game = get_game_struct();
// 	sprite = game->map.textures.sprite;

// 	int	x = 0;
// 	int	y = 0;
// 	int color = 0;
// 	int dx = (game->map.sprite_count % 8) * 100;
// 	int dy = (game->map.sprite_count / 8) * 100;

// 	while (x < 100)
// 	{
// 		y = 0;
// 		while (y < 100)
// 		{
// 			color = get_image_pixel(sprite, x + dx, y + dy);
// 			put_image_pixel(game->sprite, x, y, color);
// 			y += 1;
// 		}
// 		x += 1;
// 	}
// }

static void	update_frame(void)
{
	put_screen_ceiling_floor();
	put_screen_wall();
	put_minimap_floor();
	put_minimap_tiles();
	put_minimap_ray();
	put_minimap_player();
}

static void	draw_images(void)
{
	t_game	*game;
	t_point	top_left;

	game = get_game_struct();
	top_left.x = 0;
	top_left.y = 0;
	game->map.sprite_count += 0.2;
	if (game->map.sprite_count >= 19)
		game->map.sprite_count = 0;
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, game->screen->img_ptr);
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, game->minimap->img_ptr);
	put_image(game->screen->img_ptr, &top_left);
	put_image(game->minimap->img_ptr, &top_left);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, game->win);
}

int	draw_frame(void)
{
	set_player();
	update_frame();
	draw_images();
	return (0);
}
