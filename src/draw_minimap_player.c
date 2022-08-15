/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/15 14:08:03 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int draw_minimap_dirline(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.end.x += game->player.dir.x;
	line.end.y += game->player.dir.y;
	draw_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

int	draw_minimap_fov(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.start.x += game->player.dir.x - game->player.plane.x;
	line.start.y += game->player.dir.y - game->player.plane.y;
	line.end.x += game->player.dir.x + game->player.plane.x;
	line.end.y += game->player.dir.y + game->player.plane.y;
	draw_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

t_vector	dda_algo(t_vector pos, t_vector ray_dir, char **map_grid, int i)
{
	// delta.x: abs(광선길이 / ray.x), delta.y: abs(광선길이 / ray.y)
	// player에서 ray까지 거리를 1로 정하고, 모두 비율로 계산한다.
	// 그러므로 delta.x: abs(1 / ray.x), delta.y: abs(1 / ray.y)

	t_vector	delta;
	delta.x = fabsf(1 / ray_dir.x);
	delta.y = fabsf(1 / ray_dir.y);

	// 지도상의 위치
	t_vector	map_pos;
	map_pos.x = pos.x;
	map_pos.y = pos.y;

	// 초기값
	t_point		step;
	t_vector	side_dist;
	int			is_hoz;

	/*
	초기값 설정
	- 광선의 방향에 따라 값 설정
		- 방향이 음수인 경우 step은 -1, 방향이 양수인 경우 step은 +1
	- side의 시작 지점 설정
	*/
	if (ray_dir.x < 0)
	{
		step.x = -1;
		side_dist.x = (map_pos.x - map_pos.x) * delta.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (map_pos.x + 1 - map_pos.x) * delta.x;
	}
	if (ray_dir.y < 0)
	{
		step.y = -1;
		side_dist.y = (map_pos.y - map_pos.y) * delta.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (map_pos.y + 1 - map_pos.y) * delta.y;
	}

	/* 
	충돌 좌표 구하기
	- side_dist.x와 side_dist.y를 비교
	- 작은 값의 side_dist를 delta만큼 증가
	- 작은 값의 side 좌표를 1만큼 증가
	- 1 증가된 좌표에 벽이 있는지 확인
	*/
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta.x;
			map_pos.x += step.x;
			is_hoz = 0;
		}
		else
		{
			side_dist.y += delta.y;
			map_pos.y += step.y;
			is_hoz = 1;
		}
		if (map_grid[(int)(map_pos).y][(int)(map_pos).x] == MAP_WALL)
			break;
	}

	// 카메라 평면에서 충돌 지점까지 수직거리
	float		perpWallDist;
	t_vector	p;
	
	p.x = pos.x + (map_pos.x - pos.x + (1 - step.x) / 2);
	p.y = pos.y + (map_pos.y - pos.y + (1 - step.y) / 2);
	
	float wall;
	if (is_hoz == 0)
	{
		perpWallDist = (map_pos.x  - pos.x + (1 - step.x) / 2) / ray_dir.x;
		wall = pos.y + perpWallDist * ray_dir.y;
		p.y = wall;
	}
	else
	{
		perpWallDist = (map_pos.y - pos.y + (1 - step.y) / 2) / ray_dir.y;
		wall = pos.x + perpWallDist * ray_dir.x;
		p.x = wall;
	}

	draw_line(pos, p, MINIMAP_RAY_COLOR);

	//Calculate height of line to draw on screen
	int h = 200;
	int lineHeight = (int)(h / perpWallDist);

	// lineHeight 처리
	
	return (p);
}

int	draw_minimap_ray(void)
{
	t_game		*game;
	t_player	*player;
	t_line		line;
	int			i;
	int			w = 20;

	game = get_game_struct();
	player = &(game->player);
	line.start = game->player.pos;
	line.end = game->player.pos;
	i = 0;
	while (i <= w)
	{
		double cameraX = 2 * i / (double)(w) - 1;
		line.end.x = player->dir.x + player->plane.x * cameraX;
		line.end.y = player->dir.y + player->plane.y * cameraX;
		dda_algo(line.start, line.end, game->map.array, i);
		i += 1;
	}
	return (0);
}

int	draw_minimap_player(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.start.x *= MINIMAP_PLAYER_HEIGHT;
	line.start.y *= MINIMAP_PLAYER_WIDTH;
	line.end.x *= MINIMAP_PLAYER_HEIGHT;
	line.end.y *= MINIMAP_PLAYER_WIDTH;
	draw_rect(line.start, line.end, MINIMAP_PLAYER_COLOR);
	return (0);
}

int erase_minimap_dirline(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.end.x += game->player.dir.x;
	line.end.y += game->player.dir.y;
	draw_line(line.start, line.end, 0);
	return (0);
}

int	erase_minimap_fov(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start = game->player.pos;
	line.end = game->player.pos;
	line.start.x += game->player.dir.x - game->player.plane.x;
	line.start.y += game->player.dir.y - game->player.plane.y;
	line.end.x += game->player.dir.x + game->player.plane.x;
	line.end.y += game->player.dir.y + game->player.plane.y;
	draw_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

int	erase_minimap_ray(void)
{
	t_game		*game;
	t_player	*player;
	t_line		line;
	int			i;
	int			w = 20;

	game = get_game_struct();
	player = &(game->player);
	line.start = game->player.pos;
	line.end = game->player.pos;
	i = 0;
	while (i <= w)
	{
		double cameraX = 2 * i / (double)(w) - 1;
		line.end.x = player->pos.x + player->dir.x + player->plane.x * cameraX;
		line.end.y = player->pos.y + player->dir.y + player->plane.y * cameraX;
		draw_line(line.start, line.end, MINIMAP_RAY_COLOR);
		i += 1;
	}
	return (0);
}

int	erase_minimap_player(void)
{
	t_game		*game;
	t_vector	start;
	t_vector	end;

	game = get_game_struct();
	start.x = game->player.pos.x - (MINIMAP_PLAYER_HEIGHT / 2);
	start.y = game->player.pos.y - (MINIMAP_PLAYER_WIDTH / 2);
	end.x = game->player.pos.x + (MINIMAP_PLAYER_HEIGHT / 2);
	end.y = game->player.pos.y + (MINIMAP_PLAYER_WIDTH / 2);
	draw_rect(start, end, 0);
	return (0);
}
