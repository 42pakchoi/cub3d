/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:26:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 23:17:43 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_perpendicular_wall_dist(
	t_dda *dda, t_vector player_pos, t_vector ray_dir)
{
	if (dda->wall_dir == WALL_DIR_E || dda->wall_dir == WALL_DIR_W)
	{
		dda->wall_dist = (dda->player_grid.x - player_pos.x
				+ (1 - dda->step.x) / 2) / ray_dir.x;
	}
	else
	{
		dda->wall_dist = (dda->player_grid.y - player_pos.y
				+ (1 - dda->step.y) / 2) / ray_dir.y;
	}
}

static void	set_collision_point(t_dda *dda)
{
	if (dda->wall_dir == WALL_DIR_N || dda->wall_dir == WALL_DIR_S)
		dda->wall_collision_point = dda->player_pos.x
			+ dda->wall_dist * dda->ray_dir.x;
	else
		dda->wall_collision_point = dda->player_pos.y
			+ dda->wall_dist * dda->ray_dir.y;
	dda->wall_collision_point -= floor(dda->wall_collision_point);
}

static void	calc_dda(t_dda *dda)
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

static void	set_wall_except_(t_dda *dda, char **map_grid, int x, int y)
{
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
			|| map_grid[y + 1][x] == MAP_DOOR_OPEN
			|| map_grid[y][x - 1] == MAP_DOOR_OPEN
			|| map_grid[y][x + 1] == MAP_DOOR_OPEN)
		{
			dda->wall_dir = WALL_DOOR_SIDE;
		}
		dda->is_door = 0;
	}
}

void	calc_collision_point(char **map_grid, t_dda *dda)
{
	int	x;
	int	y;
	int	is_door;
	int	is_fire;

	is_door = 0;
	is_fire = 0;
	while (1)
	{
		calc_dda(dda);
		x = (int)(dda->player_grid).x;
		y = (int)(dda->player_grid).y;
		if (map_grid[y][x] == MAP_DOOR)
		{
			dda->is_door = 1;
			break ;
		}
		if (map_grid[y][x] == MAP_DOOR_OPEN)
			is_door = 2;
		if (map_grid[y][x] == MAP_WALL_FIRE)
		{
			is_fire = 1;
			break ;
		}
		if (map_grid[y][x] == MAP_WALL)
			break ;
	}
	set_perpendicular_wall_dist(dda, dda->player_pos, dda->ray_dir);
	set_collision_point(dda);
	if ((dda->wall_dir == WALL_DIR_N || dda->wall_dir == WALL_DIR_E))
		dda->wall_collision_point = 1 - dda->wall_collision_point;
	if (is_door == 1)
		dda->wall_dir = WALL_DOOR;
	if (is_fire == 1)
		dda->wall_dir = WALL_FIRE;
	if (is_door == 2)
	{
		if (map_grid[y][x] == MAP_DOOR_OPEN
			|| map_grid[y + 1][x] == MAP_DOOR_OPEN
			|| map_grid[y][x - 1] == MAP_DOOR_OPEN
			|| map_grid[y][x + 1] == MAP_DOOR_OPEN)
		{
			dda->wall_dir = WALL_DOOR_SIDE;
		}
	}
	set_wall_except_(dda, map_grid, x, y);
}
