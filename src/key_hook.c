/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:16:16 by cpak              #+#    #+#             */
/*   Updated: 2022/08/15 17:55:46 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_down_hook(int keycode)
{
	t_game	*game;

	game = get_game_struct();

	if (keycode == KEY_W)
		game->player.pos.y += -0.2;
	if (keycode == KEY_A)
		game->player.pos.x += -0.2;
	if (keycode == KEY_S)
		game->player.pos.y += 0.2;
	if (keycode == KEY_D)
		game->player.pos.x += 0.2;
	if (keycode == KEY_ARROW_LEFT)
		rotate_player(game, 355);
	if (keycode == KEY_ARROW_RIGHT)
		rotate_player(game, 5);
	return (0);
}

int	key_up_hook(int keycode)
{
	t_game	*game;

	draw_frame();
	game = get_game_struct();
	if (keycode == KEY_W)
		game->player.pos.y = 0;
	if (keycode == KEY_A)
		game->player.pos.x = 0;
	if (keycode == KEY_S)
		game->player.pos.y = 0;
	if (keycode == KEY_D)
		game->player.pos.x = 0;
	if (keycode == KEY_ARROW_LEFT)
		game->player.delta.angle = 0;
	if (keycode == KEY_ARROW_RIGHT)
		game->player.delta.angle = 0;
	return (0);
}
