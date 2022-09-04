/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:26:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/04 23:42:55 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static int	get_wall_except(t_dda *dda, char **map_grid, int x, int y)
{
	if (map_grid[y][x] == MAP_DOOR)
	{
		dda->is_door = MAP_DOOR;
		return (1);
	}
	if (map_grid[y][x] == MAP_DOOR_OPEN)
	{
		dda->is_door = MAP_DOOR_OPEN;
		dda->door_pos.x = x;
		dda->door_pos.y = y;
	}
	if (map_grid[y][x] == MAP_WALL_FIRE)
	{
		dda->is_fire = 1;
		return (1);
	}
	if (map_grid[y][x] == MAP_WALL)
		return (1);
	return (0);
}

static void	set_wall_except(t_dda *dda, int x, int y)
{
	if ((dda->wall_dir == WALL_DIR_N || dda->wall_dir == WALL_DIR_E))
		dda->wall_collision_point = 1 - dda->wall_collision_point;
	if (dda->is_door == MAP_DOOR)
		dda->wall_dir = WALL_DOOR;
	if (dda->is_door == MAP_DOOR_OPEN)
	{
		if (((dda->door_pos.x - 1 <= x && dda->door_pos.x + 1 >= x)
				&& dda->door_pos.y == y)
			|| ((dda->door_pos.y - 1 <= y && dda->door_pos.y + 1 >= y)
				&& dda->door_pos.x == x))
			dda->wall_dir = WALL_DOOR_SIDE;
	}
	if (dda->is_fire)
		dda->wall_dir = WALL_FIRE;
	dda->is_fire = 0;
	dda->is_door = 0;
	dda->door_pos.x = 0;
	dda->door_pos.y = 0;
}

void	calc_collision_point(char **map_grid, t_dda *dda)
{
	int	x;
	int	y;

	x = (int)dda->player_grid.x;
	y = (int)dda->player_grid.y;
	if (map_grid[y][x] == MAP_DOOR_OPEN)
	{
		dda->is_door = MAP_DOOR_OPEN;
		dda->door_pos.x = x;
		dda->door_pos.y = y;
	}
	while (1)
	{
		calc_dda(dda);
		x = (int)(dda->player_grid).x;
		y = (int)(dda->player_grid).y;
		if (get_wall_except(dda, map_grid, x, y))
			break ;
	}
	set_perpendicular_wall_dist(dda, dda->player_pos, dda->ray_dir);
	set_collision_point(dda);
	set_wall_except(dda, x, y);
}
