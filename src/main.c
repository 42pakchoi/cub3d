/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:33:12 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 02:44:21 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	run_game(char *map_filepath)
{
	t_game	*game;

	game = get_game_struct();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");

	prepare_map(map_filepath);
	init_images();
	draw_frame();

	mlx_loop(game->mlx);
}

int	main(int argc, char *argv[])
{
	if (argc == 2)
		run_game(argv[1]);
	else
		ft_putstr_fd("usage: ./cub3d <map_file_name>\n", 1);
	return (0);
}
