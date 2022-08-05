/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/04 17:51:42 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int draw_minimap_dirline(void)
{
	t_game		*game;
	t_vector	start;
	t_vector	end;

	game = get_game_struct();
	start.x = game->player_pos.x;
	start.y = game->player_pos.y;
	end.x = game->player_pos.x + game->player_dir.x;
	end.y = game->player_pos.y + game->player_dir.y;
	draw_line(start, end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

int	draw_minimap_player(void)
{
	t_game		*game;
	t_vector	start;
	t_vector	end;
	
	game = get_game_struct();
	start.x = game->player_pos.x - (MINIMAP_PLAYER_HEIGHT / 2);
	start.y = game->player_pos.y - (MINIMAP_PLAYER_WIDTH / 2);
	end.x = game->player_pos.x + (MINIMAP_PLAYER_HEIGHT / 2);
	end.y = game->player_pos.y + (MINIMAP_PLAYER_WIDTH / 2);
	draw_rect(start, end, MINIMAP_PLAYER_COLOR);
	return (0);
}
