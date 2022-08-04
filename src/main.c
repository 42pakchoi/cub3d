/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:33:12 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/04 13:10:10 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game	*data;

	if (argc == 2)
	{
		// TODO: run the game
		ft_putstr_fd("map file name: ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd("\n", 1);

		data = malloc(sizeof(t_game));
		data->mlx = mlx_init();
		data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDWO_HEIGHT, "cub3d");

		mlx_clear_window(data->mlx, data->win);
		mlx_loop_hook(data->mlx, draw_frame, data);
		mlx_loop(data->mlx);
	}
	else
		ft_putstr_fd("usage: ./cub3d <map_file_name>\n", 1);
	return (0);
}
