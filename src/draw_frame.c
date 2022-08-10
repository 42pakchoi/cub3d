/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:34:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/10 14:16:46 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_frame(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	erase_minimap_dirline();
	erase_minimap_fov();
	// erase_minimap_ray();
	// erase_minimap_player();
}

void	set_frame(t_game *game)
{
	t_player	*player;
	t_point		origin_pos;

	player = &(game->player);

	// set grid pos
	origin_pos.x = player->pos.x - (player->grid_pos.x * MINIMAP_TILE_SIZE);
	origin_pos.y = player->pos.y - (player->grid_pos.y * MINIMAP_TILE_SIZE);
	if (origin_pos.x + player->delta.x < 0)
		player->grid_pos.x -= 1;
	if (origin_pos.x + player->delta.x > MINIMAP_TILE_SIZE)
		player->grid_pos.x += 1;
	if (origin_pos.y + player->delta.y < 0)
		player->grid_pos.y -= 1;
	if (origin_pos.y + player->delta.y > MINIMAP_TILE_SIZE)
		player->grid_pos.y += 1;

	// set pos
	if (player->delta.x != 0)
		player->pos.x += player->delta.x;
	if (player->delta.y != 0)
		player->pos.y += player->delta.y;
	if (player->delta.angle != 0)
		rotate_player(game, player->delta.angle);
}

int	draw_frame(void)
{
	t_game	*game;

	game = get_game_struct();
	init_frame(game); // clear window
	set_frame(game); // calculate player position and direction
	// draw frame
	put_minimap();
	draw_minimap_dirline();
	draw_minimap_fov();
	draw_minimap_ray();
	// draw_minimap_player();
	return (0);
}
