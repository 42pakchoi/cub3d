/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:33:12 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/03 16:54:59 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	if (argc == 2)
	{
		// TODO: run the game
		ft_putstr_fd("map file name: ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("usage: ./cub3d <map_file_name>\n", 1);

	t_game	*data;

	data = malloc(sizeof(t_game));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 300, 300, "cub3d");

	mlx_clear_window(data->mlx, data->win);
	mlx_loop(data->mlx);
	return (0);
}
