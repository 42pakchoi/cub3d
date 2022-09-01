/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:31:28 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*
** static as global variable
*/
t_game	*get_game_struct(void)
{
	static t_game	game;

	return (&game);
}
