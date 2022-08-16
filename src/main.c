/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:33:12 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/16 15:55:00 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx()
{
	t_game	*game;

	game = get_game_struct();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	mlx_mouse_hook(game->win, mouse_hook, NULL);
	mlx_hook(game->win, 2, 0L, key_down, NULL);
	mlx_hook(game->win, 3, 0L, key_up, NULL);
	mlx_loop_hook(game->mlx, draw_frame, NULL);
}

void	run_game(char *filepath)
{
	t_game	*game;

	game = get_game_struct();
	init_map(filepath);
	init_player();
	init_mlx();
	mlx_loop(game->mlx);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putstr_fd("usage: ./cub3d <map_file_name>\n", 2);
		return (1);
	}
	printf("<info> map file name: %s\n", argv[1]);
	run_game(argv[1]);
	return (0);
}
