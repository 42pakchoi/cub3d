/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:26:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/28 23:54:35 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	set_perpendicular_wall_dist(t_dda *dda, t_vector player_pos, t_vector ray_dir)
{
	if (dda->wall_dir == WALL_DIR_E || dda->wall_dir == WALL_DIR_W)
		dda->wall_dist = (dda->player_grid.x  - player_pos.x + (1 - dda->step.x) / 2) / ray_dir.x;
	else
		dda->wall_dist = (dda->player_grid.y - player_pos.y + (1 - dda->step.y) / 2) / ray_dir.y;
}

static void	set_collision_point(t_dda *dda)
{
	if (dda->wall_dir == WALL_DIR_N || dda->wall_dir == WALL_DIR_S)
		dda->wall_collision_point = dda->player_pos.x + dda->wall_dist * dda->ray_dir.x;
	else
		dda->wall_collision_point = dda->player_pos.y + dda->wall_dist * dda->ray_dir.y;
	dda->wall_collision_point -= floor(dda->wall_collision_point);
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

void	calc_collision_point(char **map_grid, t_dda *dda)
{
	int x;
	int y;

	while (1)
	{
		calc_dda(dda);
		x = (int)(dda->player_grid).x;
		y = (int)(dda->player_grid).y;
		if (map_grid[y][x] == MAP_DOOR)
		{
			dda->is_door = 1;
			break;
		}
		if (map_grid[y][x] == MAP_DOOR_OPEN)
			dda->is_door = 2;
		if (map_grid[y][x] == MAP_WALL)
			break;
	}
	set_perpendicular_wall_dist(dda, dda->player_pos, dda->ray_dir);
	set_collision_point(dda);
	if ((dda->wall_dir == WALL_DIR_N || dda->wall_dir == WALL_DIR_E))
		dda->wall_collision_point = 1 - dda->wall_collision_point;
	if (dda->is_door == 1)
	{
		dda->wall_dir = WALL_DOOR;
		dda->is_door = 0;
	}
	if (dda->is_door == 2)
	{
		if (map_grid[y][x] == MAP_DOOR_OPEN 
			|| map_grid[y+1][x] == MAP_DOOR_OPEN
			|| map_grid[y][x-1] == MAP_DOOR_OPEN 
			|| map_grid[y][x+1] == MAP_DOOR_OPEN)
		{
			dda->wall_dir = WALL_DOOR_SIDE;
		}
		dda->is_door = 0;
	}
}
