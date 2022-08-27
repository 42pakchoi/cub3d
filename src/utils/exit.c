/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:43:59 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/27 03:56:30 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game_map()
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

void	free_mlx_image(t_img *img)
{
	t_game	*game;

	game = get_game_struct();

	if (img == NULL || img->img_ptr == NULL)
		return ;
	mlx_destroy_image(game->mlx, img->img_ptr);
	free(img);
}

void	free_game_textures()
{
	t_game	*game;

	game = get_game_struct();
	free_mlx_image(game->map.textures.north);
	free_mlx_image(game->map.textures.south);
	free_mlx_image(game->map.textures.west);
	free_mlx_image(game->map.textures.east);
	free_mlx_image(game->map.textures.minimap_floor);
	free_mlx_image(game->map.textures.minimap_wall);
}

void	free_game()
{
	t_game	*game;

	game = get_game_struct();
	free_game_map();
	free_game_textures();
	free_mlx_image(game->minimap);
	free_mlx_image(game->screen);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);

	exit(0);
}

void	exit_with_error(char *message)
{
	ft_putstr_fd("<Error> ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	free_game();
	system("leaks cub3d");
	exit(EXIT_FAILURE);
}

int	exit_with_close_button(void)
{
	free_game();
	system("leaks cub3d");
	printf("<info> Bye!\n");
	exit(EXIT_SUCCESS);
	return (0);
}
