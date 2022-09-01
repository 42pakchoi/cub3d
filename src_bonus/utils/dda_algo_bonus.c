/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:44:19 by cpak              #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	set_dda_side(t_dda *dda)
{
	if (dda->ray_dir.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (dda->player_pos.x - dda->player_grid.x)
			* dda->delta_dist.x;
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = (dda->player_grid.x + 1 - dda->player_pos.x)
			* dda->delta_dist.x;
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (dda->player_pos.y - dda->player_grid.y)
			* dda->delta_dist.y;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = (dda->player_grid.y + 1 - dda->player_pos.y)
			* dda->delta_dist.y;
	}
}

void	init_dda(t_dda *dda)
{
	dda->delta_dist.x = fabsf(1 / dda->ray_dir.x);
	dda->delta_dist.y = fabsf(1 / dda->ray_dir.y);
	dda->player_grid.x = (int)dda->player_pos.x;
	dda->player_grid.y = (int)dda->player_pos.y;
	set_dda_side(dda);
}

void	calc_dda(t_dda *dda)
{
	if (dda->side_dist.x < dda->side_dist.y)
	{
		dda->side_dist.x += dda->delta_dist.x;
		dda->player_grid.x += dda->step.x;
		if (dda->ray_dir.x > 0)
			dda->wall_dir = WALL_DIR_W;
		else
			dda->wall_dir = WALL_DIR_E;
	}
	else
	{
		dda->side_dist.y += dda->delta_dist.y;
		dda->player_grid.y += dda->step.y;
		if (dda->ray_dir.y > 0)
			dda->wall_dir = WALL_DIR_N;
		else
			dda->wall_dir = WALL_DIR_S;
	}
}
