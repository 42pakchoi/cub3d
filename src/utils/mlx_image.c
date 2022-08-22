/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:58:15 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/22 17:08:51 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_color_image(t_img *image, unsigned int color)
{
	int		h;
	int		w;

	h = 0;
	while (h < image->height)
	{
		w = 0;
		while (w < image->width)
		{
			put_image_pixel(image, w, h, color);
			w++;
		}
		h++;
	}
}

t_img	*make_mlx_image(int width, int height, int color)
{
	t_game	*game;
	t_img	*image;

	game = get_game_struct();
	image = (t_img *)malloc(sizeof(t_img));
	image->img_ptr = mlx_new_image(game->mlx, width, height);
	if (!image->img_ptr)
		return (NULL);
	image->addr = (int *)mlx_get_data_addr(
		image->img_ptr,
		&(image->bits_per_pixel),
		&(image->size_line),
		&(image->endian)
	);
	image->width = width;
	image->height = height;
	fill_color_image(image, mlx_get_color_value(game->mlx, color));
	return (image);
}

t_img	*get_png_image(char *filepath)
{
	t_game	*game;
	t_img	*image;

	game = get_game_struct();
	image = (t_img *)malloc(sizeof(t_img));
	image->img_ptr = mlx_png_file_to_image(game->mlx, filepath, &(image->width), &(image->height));
	if (!image->img_ptr)
		return (NULL);
	image->addr = (int *)mlx_get_data_addr(
		image->img_ptr,
		&(image->bits_per_pixel),
		&(image->size_line),
		&(image->endian)
	);

	int len = image->size_line * image->bits_per_pixel / 8;
	
	
	printf("%s, w: %d, h: %d, bpp: %d, sl: %d, endian: %d, len: %d\n",
		filepath, image->width, image->height, image->bits_per_pixel, image->size_line, image->endian, len);
	return (image);
}

void	put_image(void *img_ptr, t_point *img_pos)
{
	t_game	*game;

	game = get_game_struct();
	mlx_put_image_to_window(game->mlx, game->win, img_ptr,img_pos->x, img_pos->y);
}
