/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:33:12 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 17:42:48 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./cub3d <map_file_name>\n", 1);
		return (1);
	}
	printf("<info> map file name: %s\n", argv[1]);
	prepare_map(argv[1]);
	prepare_player();

	game = get_game_struct();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");

	mlx_mouse_hook(game->win, mouse_hook, NULL);
	mlx_hook(game->win, 2, 0L, key_down_hook, NULL);
	mlx_hook(game->win, 3, 0L, key_up_hook, NULL);
	mlx_loop_hook(game->mlx, draw_frame, NULL);
	mlx_loop(game->mlx);
	return (0);
}
