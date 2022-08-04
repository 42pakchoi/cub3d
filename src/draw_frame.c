/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/04 13:09:15 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_frame(t_game *data)
{
	mlx_clear_window(data->mlx, data->win);

	// 임시 player.pos
	data->player_pos.x = 50;
	data->player_pos.y = 50;
	data->player_dir.x = 0;
	data->player_dir.y = 20;

	draw_minimap_dirline(data);
	draw_minimap_player(data);

	return (0);
}
