/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
