/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_screen_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:21:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/05 17:26:41 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_img	*get_texture_img(int wall_dir)
{
	t_game	*game;
	t_img	*texture;

	texture = NULL;
	game = get_game_struct();
	if (wall_dir == WALL_DIR_N)
		texture = game->map.textures.north;
	else if (wall_dir == WALL_DIR_S)
		texture = game->map.textures.south;
	else if (wall_dir == WALL_DIR_E)
		texture = game->map.textures.east;
	else if (wall_dir == WALL_DIR_W)
		texture = game->map.textures.west;
	else if (wall_dir == WALL_FIRE)
		texture = game->map.textures.fire[(int)(game->map.sprite_count)];
	else if (wall_dir == WALL_DOOR)
		texture = game->map.textures.door;
	else if (wall_dir == WALL_DOOR_SIDE)
		texture = game->map.textures.door_side;
	return (texture);
}

static	void	calc_line(
	t_line *line, float line_height, t_img *texture, t_vector *texture_pos)
{
	line->end.y = line_height / 2 + WINDOW_HEIGHT / 2 - 1;
	if (line->end.y >= WINDOW_HEIGHT)
		line->end.y = WINDOW_HEIGHT - 1;
	line->start.y = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (line->start.y < 0)
	{
		texture_pos->y = (float)(texture->height)
			/ (float)line_height * (int)line->start.y * -1;
		line->start.y -= (int)line->start.y;
	}
}

static void	put_wall_line(int x, t_dda dda)
{
	t_game		*game;
	t_img		*texture;
	t_vector	texture_p;
	float		line_height;
	t_line		line;

	game = get_game_struct();
	texture = get_texture_img(dda.wall_dir);
	texture_p.x = (int)((float)(texture->width) * dda.wall_collision_point);
	texture_p.y = 0;
	line_height = ((float)WINDOW_HEIGHT / dda.wall_dist);
	calc_line(&line, line_height, texture, &texture_p);
	while (line.start.y < line.end.y)
	{
		texture_p.y += (float)(texture->height) / (float)line_height;
		line.start.y++;
		if (line.start.y <= 0)
			continue ;
		if (line.start.y >= WINDOW_HEIGHT)
			break ;
		if ((int)texture_p.x < texture->width
			&& (int)texture_p.y < texture->height)
			put_image_pixel(game->screen, x, line.start.y,
				get_image_pixel(texture, (int)texture_p.x, (int)texture_p.y));
	}
}

// 화면에 벽을 그리기 위해서 가장 중요한 것은 벽과 플레이어의 거리이다. 
// 떨어진 거리에 따라서 벽이 그려지는데, 그려지는 벽은 세로 방향으로 잘려서 출력된다. 
// 벽과의 거리를 구하기 위해서 ray casting이 사용된다.
// ray casting을 효율적으로 구현하기 위해서 dda 알고리즘을 사용했다. 
// dda 알고리즘은 어떠한 기준에 따라서 x방향이나 y방향으로 한칸씩 이동하는 알고리즘이다. 
// ray casting에서는 광선을 기준으로 dda 알고리즘이 동작한다.
// 광선이 x축 또는 y축에 도달하는 거리를 비교하여 작은 쪽의 축을 이동시킨다. 
// 광선이 충돌되면 충돌된 좌표와 충돌된 측면을 알게 된다. 
// 

int	put_screen_wall(void)
{
	t_game		*game;
	float		camera_x;
	t_dda		dda;
	int			w;

	game = get_game_struct();
	dda.player_pos = game->player.pos;
	dda.player_pos = game->player.pos;
	w = 0;
	while (w < WINDOW_WIDTH)
	{
		camera_x = 2 * w / (float)WINDOW_WIDTH - 1;
		dda.ray_dir.x = game->player.dir.x + game->player.plane.x * camera_x;
		dda.ray_dir.y = game->player.dir.y + game->player.plane.y * camera_x;
		init_dda(&dda);
		calc_collision_point(game->map.array, &dda);
		put_wall_line(w, dda);
		w += 1;
	}
	return (0);
}

int	put_screen_ceiling_floor(void)
{
	t_game		*game;
	t_point		ceiling_start;
	t_point		ceiling_end;
	t_point		floor_start;
	t_point		floor_end;

	game = get_game_struct();
	ceiling_start.x = 0;
	ceiling_start.y = 0;
	ceiling_end.x = WINDOW_WIDTH;
	ceiling_end.y = WINDOW_HEIGHT / 2;
	floor_start.x = 0;
	floor_start.y = WINDOW_HEIGHT / 2;
	floor_end.x = WINDOW_WIDTH;
	floor_end.y = WINDOW_HEIGHT;
	put_image_rect(
		game->screen, ceiling_start, ceiling_end, game->map.ceiling_color);
	put_image_rect(game->screen, floor_start, floor_end, game->map.floor_color);
	return (FT_SUCCESS);
}
