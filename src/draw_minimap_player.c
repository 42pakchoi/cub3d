/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:28:45 by cpak              #+#    #+#             */
/*   Updated: 2022/08/08 17:48:31 by sarchoi          ###   ########seoul.kr  */
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

int	draw_minimap_ray(void)
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
		draw_line(game->player.pos, end, MINIMAP_RAY_COLOR);
		i += 1;
	}
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
