/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:43:16 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 19:04:26 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	copy_char(
	t_list *map_start_line, char **map_array, size_t i, size_t j)
{
	if (ft_strlen(map_start_line->content) > (int)j)
		map_array[i][j] = *(char *)(map_start_line->content + j);
	else
		map_array[i][j] = MAP_OUTSIDE;
}

char	**get_map_array(t_list *map_start_line, size_t h, size_t w)
{
	char	**map_array;
	size_t	i;
	size_t	j;

	map_array = (char **)malloc(sizeof(char *) * h + 1);
	if (map_array == NULL)
		return (NULL);
	map_array[h] = NULL;
	i = 0;
	while (i < h)
	{
		map_array[i] = malloc(sizeof(char) * w + 1);
		if (map_array[i] == NULL)
			return (NULL);
		map_array[i][w] = '\0';
		j = 0;
		while (j < w)
		{
			copy_char(map_start_line, map_array, i, j);
			j++;
		}
		i++;
		map_start_line = map_start_line->next;
	}
	return (map_array);
}
