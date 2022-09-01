/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:13:38 by sarchoi           #+#    #+#             */
/*   Updated: 2022/09/01 17:07:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_list	*find_map_line(t_list *head, char *to_find)
{
	t_list	*ptr;

	ptr = head;
	while (ptr)
	{
		if (ft_strncmp(ptr->content, to_find, ft_strlen(to_find)) == 0)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int	parse_map(void)
{
	t_game	*game;

	game = get_game_struct();
	if (game->map.raw == NULL)
		return (FT_ERROR);
	if (
		read_textures() == FT_ERROR
		|| read_colors() == FT_ERROR
		|| read_map() == FT_ERROR
	)
		return (FT_ERROR);
	return (FT_SUCCESS);
}
