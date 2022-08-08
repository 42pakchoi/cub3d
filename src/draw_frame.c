/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/08 10:34:25 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_frame(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	erase_minimap_dirline();
	erase_minimap_fov();
	erase_minimap_player();
}

static void	set_frame(t_game *game)
{
	game->player_pos.x += game->player_mov.x;
	game->player_pos.y += game->player_mov.y;
	game->player_dir = calc_rotated_vector(game->player_dir, game->player_angl);
	game->fov.start = calc_rotated_vector(game->fov.start, game->player_angl);
	game->fov.end = calc_rotated_vector(game->fov.end, game->player_angl);
}

int	draw_frame(void)
{
	t_game	*game;

	game = get_game_struct();
	init_frame(game);
	set_frame(game);
	draw_minimap_dirline();
	draw_minimap_fov();
	draw_minimap_player();
	return (0);
}
