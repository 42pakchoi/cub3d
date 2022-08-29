/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:43:59 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 23:13:19 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
