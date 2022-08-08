/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:58:15 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/08 15:14:53 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_color_image(t_img *image, int width, int height, int color)
{
	int	h;
	int	w;

	h = 0;
	while (h < height)
	{
		w = 0;
		while (w < width)
		{
			image->addr[h * width + w] = color;
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
	fill_color_image(image, width, height, color);
	return (image);
}

void	*get_png_image(char *filepath)
{
	t_game	*game;
	void	*img_ptr;
	int		width;
	int		height;

	game = get_game_struct();
	img_ptr = mlx_png_file_to_image(game->mlx, filepath, &width, &height);
	if (img_ptr == NULL)
		return (NULL);
	return (img_ptr);
}

void	put_image(void *img_ptr, t_vector *img_pos)
{
	t_game	*game;

	game = get_game_struct();
	mlx_put_image_to_window(game->mlx, game->win, img_ptr, \
		img_pos->x, img_pos->y);
}
