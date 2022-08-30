/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:26:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/30 21:56:50 by cpak             ###   ########seoul.kr  */
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

static void	set_wall_except(t_dda *dda, char **map_grid, int x, int y)
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
		if ((map_grid[y - 1] != 0 && map_grid[y - 1][x] == MAP_DOOR_OPEN)
			|| (map_grid[y + 1] != 0 && map_grid[y + 1][x] == MAP_DOOR_OPEN)
			|| (map_grid[y][x - 1] != 0 && map_grid[y][x - 1] == MAP_DOOR_OPEN)
			|| (map_grid[y][x + 1] != 0 && map_grid[y][x + 1] == MAP_DOOR_OPEN))
		{
			dda->wall_dir = WALL_DOOR_SIDE;
		}
		dda->is_door = 0;
	}
	if (dda->is_fire)
	{
		dda->wall_dir = WALL_FIRE;
		dda->is_fire = 0;
	}
}

int	get_wall_except(t_dda *dda, char **map_grid, int x, int y)
{
	if (map_grid[y][x] == MAP_DOOR)
	{
		dda->is_door = 1;
		return (1);
	}
	if (map_grid[y][x] == MAP_DOOR_OPEN)
		dda->is_door = 2;
	if (map_grid[y][x] == MAP_WALL_FIRE)
	{
		dda->is_fire = 1;
		return (1);
	}
	if (map_grid[y][x] == MAP_WALL)
		return (1);
	return (0);
}

int	calc_collision_point(char **map_grid, t_dda *dda)
{
	t_game	*game;
	int		x;
	int		y;

	game = get_game_struct();
	if (map_grid[dda->player_grid.y][dda->player_grid.x] == MAP_DOOR_OPEN)
			dda->is_door = 2;
	while (1)
	{
		calc_dda(dda);
		x = (int)(dda->player_grid).x;
		y = (int)(dda->player_grid).y;
		if (x < 0 || x >= (int)game->map.width || y < 0 || y >= (int)game->map.height)
			return (0);
		if (get_wall_except(dda, map_grid, x, y))
			break ;
	}
	set_perpendicular_wall_dist(dda, dda->player_pos, dda->ray_dir);
	set_collision_point(dda);
	set_wall_except(dda, map_grid, x, y);
	return (1);
}
