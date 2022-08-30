/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:18:47 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/15 18:23:32 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_minimap_ray_line(t_dda *dda)
{
	t_game		*game;
	t_line		ray;

	game = get_game_struct();
	ray.start = dda->player_pos;
	ray.end.x = dda->player_pos.x + dda->wall_dist * dda->ray_dir.x;
	ray.end.y = dda->player_pos.y + dda->wall_dist * dda->ray_dir.y;
	if ((ray.start.x > 0 || ray.start.x < game->map.width)
		&& (ray.start.y > 0 || ray.start.y < game->map.height))
		put_minimap_line(ray.start, ray.end);
}

int	put_minimap_ray(void)
{
	t_game		*game;
	t_player	*player;
	int			w;
	float		camera_x;
	t_dda		dda;

	game = get_game_struct();
	player = &(game->player);
	dda.player_pos = player->pos;
	dda.player_pos = player->pos;
	w = 0;
	while (w < WINDOW_WIDTH)
	{
		camera_x = 2 * w / (float)WINDOW_WIDTH - 1;
		dda.ray_dir.x = player->dir.x + player->plane.x * camera_x;
		dda.ray_dir.y = player->dir.y + player->plane.y * camera_x;
		init_dda(&dda);
		calc_collision_point(game->map.array, &dda);
		put_minimap_ray_line(&dda);
		w += 1;
	}
	return (0);
}
