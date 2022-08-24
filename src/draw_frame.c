/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/24 15:11:01 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_frame()
{
	t_game	*game;

	game = get_game_struct();
	// TODO: check
	// mlx_clear_window(game->mlx, game->win);
}

void	update_frame(void)
{
	put_screen();
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
	put_image(game->screen->img_ptr, &top_left);
	put_image(game->minimap->img_ptr, &top_left);
}

int	draw_frame(void)
{
	clear_frame();
	set_player();
	update_frame();
	draw_images();
	return (0);
}
