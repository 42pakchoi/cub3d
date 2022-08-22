/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:26:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/19 19:23:16 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_perpendicular_wall_dist(t_vector player_pos, t_vector ray_dir, t_dda *dda)
{
	float wall_dist;

	if (dda->wall_dir == WALL_DIR_E || dda->wall_dir == WALL_DIR_W)
		wall_dist = (dda->player_grid.x  - player_pos.x + (1 - dda->step.x) / 2) / ray_dir.x;
	else
		wall_dist = (dda->player_grid.y - player_pos.y + (1 - dda->step.y) / 2) / ray_dir.y;
	return (wall_dist);
}

void	init_dda(t_dda *dda)
{
	dda->player_pos = dda->player_pos;
	dda->ray_dir = dda->ray_dir;
	dda->delta_dist.x = fabsf(1 / dda->ray_dir.x);
	dda->delta_dist.y = fabsf(1 / dda->ray_dir.y);
	dda->player_grid.x = (int)dda->player_pos.x;
	dda->player_grid.y = (int)dda->player_pos.y;
	if (dda->ray_dir.x < 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (dda->player_pos.x - dda->player_grid.x) * dda->delta_dist.x;
	}
	else
	{
		dda->step.x = 1;
		dda->side_dist.x = (dda->player_grid.x + 1 - dda->player_pos.x) * dda->delta_dist.x;
	}
	if (dda->ray_dir.y < 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (dda->player_pos.y - dda->player_grid.y) * dda->delta_dist.y;
	}
	else
	{
		dda->step.y = 1;
		dda->side_dist.y = (dda->player_grid.y + 1 - dda->player_pos.y) * dda->delta_dist.y;
	}
}

void	calc_collision_point(char **map_grid, t_dda *dda)
{
	while (1)
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
		if (map_grid[(int)(dda->player_grid).y][(int)(dda->player_grid).x] == MAP_WALL)
			break;
	}
}
