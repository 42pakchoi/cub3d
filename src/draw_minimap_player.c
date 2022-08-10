/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/10 23:43:19 by cpak             ###   ########seoul.kr  */
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

void	dda_algo(t_vector ray, char **map, t_point grid_pos)
{
	// delta.x: abs(광선길이 / ray.x), delta.y: abs(광선길이 / ray.y)
	// player에서 ray까지 거리를 1로 정하고, 모두 비율로 계산한다.
	// 그러므로 delta.x: abs(1 / ray.x), delta.y: abs(1 / ray.y)

	t_vector	delta;
	delta.x = fabsf(1 / ray.x);
	delta.y = fabsf(1 / ray.y);

	// 지도상의 위치
	t_point	pos;
	pos = grid_pos;

	// 초기값
	t_point		step;
	t_vector	side;

	if (ray.x < 0)
	{
		step.x = -1;
		side.x = (pos.x - pos.x) * delta.x;
	}
	else
	{
		step.x = 1;
		side.x = (pos.x + 1 - pos.x) * delta.x;
	}
	if (ray.y < 0)
	{
		step.y = -1;
		side.y = (pos.y - pos.y) * delta.y;
	}
	else
	{
		step.y = 1;
		side.y = (pos.y + 1 - pos.y) * delta.y;
	}

	while (1)
	{
		if (side.x < side.y)
		{
			side.x += delta.x;
			pos.x += step.x;
		}
		else
		{
			side.y += delta.y;
			pos.y += step.y;
		}
		if (map[pos.y][pos.x] == MAP_WALL)
		{
			printf("delta.x: %f, delta.y: %f\n", delta.x, delta.y);
			printf("side.x: %f, side.y: %f\n", side.x, side.y);
			printf("pos.x: %d, pos.y: %d\n", pos.x, pos.y);
			return;
		}
	}
}

int	draw_minimap_ray(void)
{
	t_game		*game;
	// t_vector	end;
	// int			i;
	t_vector	ray;

	game = get_game_struct();
	ray.x = game->player.dir.x / MINIMAP_TILE_SIZE;
	ray.y = game->player.dir.y / MINIMAP_TILE_SIZE;

	dda_algo(ray, game->map.array, game->player.grid_pos);

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
