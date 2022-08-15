/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:16:16 by cpak              #+#    #+#             */
/*   Updated: 2022/08/14 21:24:50 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_down_hook(int keycode)
{
	t_game	*game;

	game = get_game_struct();
	if (keycode == KEY_W)
		game->player.delta.y = -0.2;
	if (keycode == KEY_A)
		game->player.delta.x = -0.2;
	if (keycode == KEY_S)
		game->player.delta.y = 0.2;
	if (keycode == KEY_D)
		game->player.delta.x = 0.2;
	if (keycode == KEY_ARROW_LEFT)
		game->player.delta.angle = 350;
	if (keycode == KEY_ARROW_RIGHT)
		game->player.delta.angle = 10;
	return (0);
}

int	key_up_hook(int keycode)
{
	t_game	*game;

	draw_frame();
	game = get_game_struct();
	if (keycode == KEY_W)
		game->player.delta.y = 0;
	if (keycode == KEY_A)
		game->player.delta.x = 0;
	if (keycode == KEY_S)
		game->player.delta.y = 0;
	if (keycode == KEY_D)
		game->player.delta.x = 0;
	if (keycode == KEY_ARROW_LEFT)
		game->player.delta.angle = 0;
	if (keycode == KEY_ARROW_RIGHT)
		game->player.delta.angle = 0;
	return (0);
}
