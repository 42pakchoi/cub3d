/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:54:02 by cpak              #+#    #+#             */
/*   Updated: 2022/08/29 23:07:04 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_image_pixel(t_img *image, int x, int y, int color)
{
	int				bytes;
	int				offset;
	unsigned int	index;

	bytes = image->bits_per_pixel / CHAR_BIT;
	offset = (image->size_line - image->width * bytes) / bytes;
	index = (image->width + offset) * y + x;
	image->addr[index] = color;
}

void	put_image_rect(t_img *image, t_point start, t_point end, int color)
{
	int		x;
	int		y;

	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		while (y < end.y)
		{
			put_image_pixel(image, x, y, color);
			y += 1;
		}
		x += 1;
	}
}
