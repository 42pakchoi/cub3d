/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 19:19:33 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/30 22:06:18 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_info(char *message)
{
	ft_putstr_fd("<Info> ", 1);
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
}

int	print_error(char *message)
{
	ft_putstr_fd("<Error> ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (FT_ERROR);
}
