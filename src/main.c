/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:33:12 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 15:33:01 by sarchoi          ###   ########seoul.kr  */
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
		printf("----1\n");
		prepare_map(argv[1]);
		printf("----2\n");

		game = get_game_struct();
		game->mlx = mlx_init();
		game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
		printf("----3\n");

		// temp init value
		game->player_pos.x = 200;
		game->player_pos.y = 200;
		game->player_dir.x = 0;
		game->player_dir.y = -30;
		game->fov.start.x = -20;
		game->fov.start.y = -30;
		game->fov.end.x = 20;
		game->fov.end.y = -30;

		int	val = -20;
		int i = 0;
		while (val <= 20)
		{
			game->ray_vec[i].x = val;
			game->ray_vec[i].y = -30;
			val += 2;
			i += 1;
		}
		printf("----4\n");

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
