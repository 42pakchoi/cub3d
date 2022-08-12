/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/08 17:42:44 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_frame(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	erase_minimap_dirline();
	erase_minimap_fov();
	erase_minimap_ray();
	erase_minimap_player();
}

void	set_frame(t_game *game)
{
	if (game->player.delta.x != 0)
		game->player.pos.x += game->player.delta.x;
	if (game->player.delta.y != 0)
		game->player.pos.y += game->player.delta.y;
	if (game->player.delta.angle != 0)
		rotate_player(game, game->player.delta.angle);
}

int	draw_frame(void)
{
	t_game	*game;

	game = get_game_struct();
	init_frame(game); // clear window
	set_frame(game); // calculate player position and direction
	// draw frame
	put_minimap();
	draw_minimap_ray();
	draw_minimap_dirline();
	draw_minimap_fov();
	draw_minimap_player();
	return (0);
}
