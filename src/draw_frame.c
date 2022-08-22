/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/22 17:07:00 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clear_frame()
{
	t_game	*game;

	game = get_game_struct();
	mlx_clear_window(game->mlx, game->win);
}

static void	update_minimap_frame(void)
{
	put_minimap_floor();
	put_minimap_tiles();
	put_minimap_ray();
	put_minimap_player();
}

static void	draw_minimap(void)
{
	t_game	*game;
	t_point	top_left;

	game = get_game_struct();
	top_left.x = 0;
	top_left.y = 0;
	put_image(game->map.textures.minimap_floor->img_ptr, &top_left);
}

int	draw_frame(void)
{
	clear_frame();
	set_player();
	draw_wall();
	update_minimap_frame();
	draw_minimap();
	return (0);
}
