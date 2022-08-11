/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/11 19:45:02 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int draw_minimap_dirline(void)
{
	t_game		*game;
	t_vector	end;

	game = get_game_struct();
	end.x = game->player.pos.x + game->player.dir.x;
	end.y = game->player.pos.y + game->player.dir.y;
	draw_line(game->player.pos, end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

int	draw_minimap_fov(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start.x = game->player.pos.x + game->player.fov.start.x;
	line.start.y = game->player.pos.y + game->player.fov.start.y;
	line.end.x = game->player.pos.x + game->player.fov.end.x;
	line.end.y = game->player.pos.y + game->player.fov.end.y;
	draw_line(line.start, line.end, MINIMAP_DIRLINE_COLOR);
	return (0);
}

void	dda_algo(t_vector pos, t_vector ray, char **map_grid)
{
	// delta.x: abs(광선길이 / ray.x), delta.y: abs(광선길이 / ray.y)
	// player에서 ray까지 거리를 1로 정하고, 모두 비율로 계산한다.
	// 그러므로 delta.x: abs(1 / ray.x), delta.y: abs(1 / ray.y)

	t_vector	delta;
	delta.x = fabsf(1 / ray_dir.x);
	delta.y = fabsf(1 / ray_dir.y);

	// 지도상의 위치
	t_point	map_pos;
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
		if (map_grid[map_pos.y][map_pos.x] == MAP_WALL)
			break;
	}

	// delta 값
	printf("delta.x: %f, delta.y: %f\n", delta.x, delta.y);

	// 충돌된 상태에서 누적된 side 값 
	printf("side_dist.x: %f, side_dist.y: %f\n", side_dist.x, side_dist.y);

	// 충돌된 벽 좌표
	printf("map.x: %d, map.y: %d\n", map.x, map.y);

	// 거리 구하기
	if (is_hoz == 0)
		printf("xside_dist, len: %f\n", side_dist.x / ray_dir.x);
	else
		printf("yside_dist, len: %f\n", side_dist.y / ray_dir.y);
}

int	draw_minimap_ray(void)
{
	t_game		*game;
	// t_vector	end;
	// int			i;
	t_vector	ray;
	t_vector	pos;

	game = get_game_struct();
	ray.x = game->player.dir.x / MINIMAP_TILE_SIZE;
	ray.y = game->player.dir.y / MINIMAP_TILE_SIZE;
	pos.x = game->player.pos.x / MINIMAP_TILE_SIZE;
	pos.y = game->player.pos.y / MINIMAP_TILE_SIZE;


	dda_algo(pos, ray, game->map.array);

	// end.x = game->player.pos.x + (game->player.rays[0].x * 5);
	// end.y = game->player.pos.y + (game->player.rays[0].y * 5);

	// draw_line(game->player.pos, end, MINIMAP_RAY_COLOR);

	// i = 0;
	// while (i <= 20)
	// {
	// 	end.x = game->player.pos.x + (game->player.rays[i].x * 5);
	// 	end.y = game->player.pos.y + (game->player.rays[i].y * 5);

	// 	draw_line(game->player.pos, end, MINIMAP_RAY_COLOR);
	// 	i += 1;
	// }
	return (0);
}

int	draw_minimap_player(void)
{
	t_game		*game;
	t_vector	start;
	t_vector	end;

	game = get_game_struct();
	start.x = game->player.pos.x - (MINIMAP_PLAYER_HEIGHT / 2);
	start.y = game->player.pos.y - (MINIMAP_PLAYER_WIDTH / 2);
	end.x = game->player.pos.x + (MINIMAP_PLAYER_HEIGHT / 2);
	end.y = game->player.pos.y + (MINIMAP_PLAYER_WIDTH / 2);
	draw_rect(start, end, MINIMAP_PLAYER_COLOR);
	return (0);
}

int erase_minimap_dirline(void)
{
	t_game		*game;
	t_vector	start;
	t_vector	end;

	game = get_game_struct();
	start.x = game->player.pos.x;
	start.y = game->player.pos.y;
	end.x = game->player.pos.x + game->player.dir.x;
	end.y = game->player.pos.y + game->player.dir.y;
	draw_line(start, end, 0);
	return (0);
}

int	erase_minimap_fov(void)
{
	t_game		*game;
	t_line		line;

	game = get_game_struct();
	line.start.x = game->player.pos.x + game->player.fov.start.x;
	line.start.y = game->player.pos.y + game->player.fov.start.y;
	line.end.x = game->player.pos.x + game->player.fov.end.x;
	line.end.y = game->player.pos.y + game->player.fov.end.y;
	draw_line(line.start, line.end, 0);
	return (0);
}

int	erase_minimap_ray(void)
{
	t_game		*game;
	t_vector	end;
	int			i;

	game = get_game_struct();
	i = 0;
	while (i <= 20)
	{
		end.x = game->player.pos.x + (game->player.rays[i].x * 5);
		end.y = game->player.pos.y + (game->player.rays[i].y * 5);
		draw_line(game->player.pos, end, 0);
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
