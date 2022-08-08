/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:33:12 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 10:35:47 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	*game;

	if (argc == 2)
	{
		// TODO: run the game
		ft_putstr_fd("map file name: ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd("\n", 1);

		game = get_game_struct();
		game->mlx = mlx_init();
		game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
		
		// temp init value
		game->player_pos.x = 200;
		game->player_pos.y = 200;
		game->player_dir.x = 0;
		game->player_dir.y = -30;
		game->fov.start.x = -15;
		game->fov.start.y = -30;
		game->fov.end.x = 15;
		game->fov.end.y = -30;

		mlx_mouse_hook(game->win, mouse_hook, NULL);
		mlx_hook(game->win, 2, 0L, key_down_hook, NULL);
		mlx_hook(game->win, 3, 0L, key_up_hook, NULL);
		mlx_loop_hook(game->mlx, draw_frame, NULL);
		mlx_loop(game->mlx);
	}
	else
		ft_putstr_fd("usage: ./cub3d <map_file_name>\n", 1);
	return (0);
}
