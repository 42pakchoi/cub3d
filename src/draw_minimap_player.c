/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/04 13:44:45 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int draw_minimap_dirline(t_game *data)
{
	t_vector	start;
	t_vector	end;

	start.x = data->player_pos.x;
	start.y = data->player_pos.y;
	end.x = data->player_pos.x + data->player_dir.x;
	end.y = data->player_pos.y + data->player_dir.y;
	draw_line(data, start, end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

int	draw_minimap_player(t_game *data)
{
	t_vector	start;
	t_vector	end;
	
	start.x = data->player_pos.x - (MINIMAP_PLAYER_HEIGHT / 2);
	start.y = data->player_pos.y - (MINIMAP_PLAYER_WIDTH / 2);
	end.x = data->player_pos.x + (MINIMAP_PLAYER_HEIGHT / 2);
	end.y = data->player_pos.y + (MINIMAP_PLAYER_WIDTH / 2);
	draw_rect(data,start, end, MINIMAP_PLAYER_COLOR);
	return (0);
}
