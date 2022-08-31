/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/31 14:19:43 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_frame(void)
{
	put_screen_ceiling_floor();
	put_screen_wall();
}

static void	draw_images(void)
{
	t_game	*game;
	t_point	top_left;

	game = get_game_struct();
	top_left.x = 0;
	top_left.y = 0;
	mlx_sync(MLX_SYNC_IMAGE_WRITABLE, game->screen->img_ptr);
	put_image(game->screen->img_ptr, &top_left);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, game->win);
}

int	draw_frame(void)
{
	set_player();
	update_frame();
	draw_images();
	return (0);
}
