/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fire_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:26:35 by cpak              #+#    #+#             */
/*   Updated: 2022/08/30 17:02:06 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_fire_image(int i)
{
	char	*num;
	char	*tmp;
	char	*result;

	num = ft_itoa(i);
	tmp = ft_strjoin(PREFIX_IMG_FIRE, num);
	result = ft_strjoin(tmp, ".png");
	free(num);
	free(tmp);
	return (result);
}

int	set_fire_texture(void)
{
	t_game	*game;
	t_map	*map;
	int		i;
	char	*path;

	game = get_game_struct();
	map = &(game->map);
	map->textures.fire = (t_img **)malloc(sizeof(t_img *) * 20);
	if (!map->textures.fire)
		return (0);
	map->textures.fire[19] = 0;
	i = 0;
	while (i < 19)
	{
		path = get_fire_image(i);
		map->textures.fire[i] = get_png_image(path);
		free(path);
		if (map->textures.fire[i] == NULL)
			return (0);
		i += 1;
	}
	return (1);
}
