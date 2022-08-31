/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:01:30 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/31 14:35:23 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_game_map(void)
{
	t_game	*game;

	game = get_game_struct();
	if (game->map.raw != NULL)
		ft_lstclear(&(game->map.raw), free);
	if (game->map.array != NULL)
		ft_split_free(game->map.array);
	if (game->map.path_north_texture != NULL)
		free(game->map.path_north_texture);
	if (game->map.path_south_texture != NULL)
		free(game->map.path_south_texture);
	if (game->map.path_west_texture != NULL)
		free(game->map.path_west_texture);
	if (game->map.path_east_texture != NULL)
		free(game->map.path_east_texture);
}

static void	free_mlx_image(t_img *img)
{
	t_game	*game;

	game = get_game_struct();
	if (img == NULL || img->img_ptr == NULL)
		return ;
	mlx_destroy_image(game->mlx, img->img_ptr);
	free(img);
}

static void	free_game_textures(void)
{
	t_game	*game;

	game = get_game_struct();
	free_mlx_image(game->map.textures.north);
	free_mlx_image(game->map.textures.south);
	free_mlx_image(game->map.textures.west);
	free_mlx_image(game->map.textures.east);
}

/*
** NOTE: Do not free `game->mlx`
** because mlx library does not provide function to free it.
** And `free()` is not stable.
*/
void	free_game(void)
{
	t_game	*game;

	game = get_game_struct();
	free_game_map();
	free_game_textures();
	free_mlx_image(game->screen);
	if (game->mlx != NULL && game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
}
