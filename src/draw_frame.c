/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/07 17:32:04 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_frame(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	erase_minimap_player();
	erase_minimap_dirline();
}

int	draw_frame(void)
{
	t_game	*game;

	game = get_game_struct();
	init_frame(game);
	game->player_pos.x += game->player_mov.x;
	game->player_pos.y += game->player_mov.y;
	draw_minimap_dirline();
	draw_minimap_player();
	return (0);
}
