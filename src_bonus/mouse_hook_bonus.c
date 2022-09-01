/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 04:34:00 by cpak              #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_down(int button, int x)
{
	t_game	*game;

	(void)button;
	game = get_game_struct();
	game->player.key.rotate_origin = x;
	game->player.key.rotate = 0;
	return (0);
}

int	mouse_move(int x)
{
	t_game	*game;

	game = get_game_struct();
	if (game->player.key.rotate_origin != 0)
		game->player.key.rotate = (x - game->player.key.rotate_origin) / -20;
	return (0);
}

int	mouse_up(void)
{
	t_game	*game;

	game = get_game_struct();
	game->player.key.rotate_origin = 0;
	game->player.key.rotate = 0;
	return (0);
}
