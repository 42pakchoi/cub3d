/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:43:59 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/30 19:22:18 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_with_error(char *message)
{
	print_error(message);
	free_game();
	exit(EXIT_FAILURE);
}

int	exit_with_close_button(void)
{
	free_game();
	print_info("Bye!");
	system("leaks cub3d");
	exit(EXIT_SUCCESS);
	return (0);
}
