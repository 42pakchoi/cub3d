/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/07 17:15:50 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_frame(void)
{
	t_game	*game;

	game = get_game_struct();
	mlx_clear_window(game->mlx, game->win);
	erase_minimap_player();
	erase_minimap_dirline();
	game->player_pos.x += game->player_mov.x;
	game->player_pos.y += game->player_mov.y;
	draw_minimap_player();
	draw_minimap_dirline();
	return (0);
}
