/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_minimap_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:08:31 by cpak              #+#    #+#             */
/*   Updated: 2022/08/29 17:28:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_quadrant_one_four(t_vector start, t_vector end)
{
	t_bres	bres;

	bres.point.x = start.x;
	bres.point.y = start.y;
	bres.size.w = end.x - start.x;
	bres.size.h = end.y - start.y;
	bres.m = (float)bres.size.h / (float)bres.size.w;
	if (bres.m > 1)
	{
		ft_swap_int(&bres.size.w, &bres.size.h);
		bres.max = end.y - bres.point.y;
	}
	else
		bres.max = end.x - bres.point.x;
	bres_algo(bres, 0);
}

static void	put_quadrant_two_three(t_vector start, t_vector end)
{
	t_bres	bres;

	bres.point.x = start.x;
	bres.point.y = start.y;
	bres.size.w = end.x - start.x;
	bres.size.h = end.y - start.y;
	bres.size.w *= -1;
	bres.m = (float)bres.size.h / (float)bres.size.w;
	if (bres.m > 1)
	{
		ft_swap_int(&bres.size.w, &bres.size.h);
		bres.max = end.y - bres.point.y;
	}
	else
	{
		bres.point.x = end.x;
		bres.point.y = end.y;
		bres.max = start.x - bres.point.x;
	}
	bres_algo(bres, 1);
}

void	put_minimap_line(t_vector start, t_vector end)
{
	t_game	*game;
	int		w;
	int		h;

	game = get_game_struct();
	start.x *= game->map.minimap_tile_size;
	start.y *= game->map.minimap_tile_size;
	end.x *= game->map.minimap_tile_size;
	end.y *= game->map.minimap_tile_size;
	w = end.x - start.x;
	h = end.y - start.y;
	if (w >= 0 && h >= 0)
		put_quadrant_one_four(start, end);
	else if (w <= 0 && h <= 0)
		put_quadrant_one_four(end, start);
	else if (w < 0)
		put_quadrant_two_three(start, end);
	else if (h < 0)
		put_quadrant_two_three(end, start);
}
