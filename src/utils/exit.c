/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:43:59 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 15:37:26 by cpak             ###   ########seoul.kr  */
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

void	free_mlx_image_array(t_img **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free_mlx_image(arr[i++]);
	free(arr);
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
	free_mlx_image(game->map.textures.door);
	free_mlx_image(game->map.textures.door_side);
	free_mlx_image_array(game->map.textures.fire);
}

/*
** NOTE: Do not free `game->mlx` because mlx library does not provide function to free it. And `free()` is not stable.
*/
void	free_game()
{
	t_game	*game;

	game = get_game_struct();
	free_game_map();
	free_game_textures();
	free_mlx_image(game->minimap);
	free_mlx_image(game->screen);
	mlx_destroy_window(game->mlx, game->win);
}

void	exit_with_error(char *message)
{
	ft_putstr_fd("<Error> ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	free_game();
	exit(EXIT_FAILURE);
}

int	exit_with_close_button(void)
{
	free_game();
	printf("<info> Bye!\n");
	system("leaks cub3d");
	exit(EXIT_SUCCESS);
	return (0);
}
