/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:16:16 by cpak              #+#    #+#             */
/*   Updated: 2022/08/08 14:50:07 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_down_hook(int keycode)
{
	t_game	*game;

	game = get_game_struct();
	if (keycode == KEY_W)
		game->player_mov.y = -5;
	if (keycode == KEY_A)
		game->player_mov.x = -5;
	if (keycode == KEY_S)
		game->player_mov.y = 5;
	if (keycode == KEY_D)
		game->player_mov.x = 5;
	if (keycode == KEY_ARROW_LEFT)
		game->player_angl = 350;
	if (keycode == KEY_ARROW_RIGHT)
		game->player_angl = 10;
	return (0);
}

int	key_up_hook(int keycode)
{
	t_game	*game;

	game = get_game_struct();
	if (keycode == KEY_W)
		game->player_mov.y = 0;
	if (keycode == KEY_A)
		game->player_mov.x = 0;
	if (keycode == KEY_S)
		game->player_mov.y = 0;
	if (keycode == KEY_D)
		game->player_mov.x = 0;
	if (keycode == KEY_ARROW_LEFT)
		game->player_angl = 0;
	if (keycode == KEY_ARROW_RIGHT)
		game->player_angl = 0;
	return (0);
}
