/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:16:16 by cpak              #+#    #+#             */
/*   Updated: 2022/08/08 00:54:36 by cpak             ###   ########seoul.kr  */
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

int	key_up_hook(void)
{
	t_game	*game;

	game = get_game_struct();
	game->player_mov.x = 0;
	game->player_mov.y = 0;
	game->player_angl = 0;
	return (0);
}
