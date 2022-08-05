/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 04:34:00 by cpak              #+#    #+#             */
/*   Updated: 2022/08/06 04:34:20 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_hook(int button, int x, int y)
{
	t_game	*game;

	(void)button;
	game = get_game_struct();
	game->player_dir.x = x - game->player_pos.x;
	game->player_dir.y = y - game->player_pos.y;
	return (0);
}
