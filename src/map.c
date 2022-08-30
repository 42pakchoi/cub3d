/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:43:07 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 18:17:49 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	vaildate_file_extension(char *filepath)
{
	char	*p;

	p = ft_strnstr(filepath, ".cub", ft_strlen(filepath));
	if (p == NULL || ft_strlen(p) != 4)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

static void	read_file(int filde)
{
	t_game	*game;
	t_map	*map;
	char	*buf;
	int		result;

	game = get_game_struct();
	map = &(game->map);
	map->raw = NULL;
	result = get_next_line(filde, &buf);
	while (result != FT_EOF)
	{
		if (map->raw == NULL)
			map->raw = ft_lstnew((void *) buf);
		else
			ft_lstadd_back(&(map->raw), ft_lstnew((void *) buf));
		result = get_next_line(filde, &buf);
	}
	free(buf);
}

static void	print_map_data(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	printf("<info> map data\n");
	printf("- height: %zu\n", map->height);
	printf("- width: %zu\n", map->width);
	printf("- path_north_texture: %s\n", map->path_north_texture);
	printf("- path_south_texture: %s\n", map->path_south_texture);
	printf("- path_west_texture: %s\n", map->path_west_texture);
	printf("- path_east_texture: %s\n", map->path_east_texture);
	printf("- rgb_floor_color: %x\n", map->floor_color);
	printf("- rgb_ceiling_color: %x\n", map->ceiling_color);
}

static void	clear_map_raw(void)
{
	t_game	*game;
	t_map	*map;

	game = get_game_struct();
	map = &(game->map);
	ft_lstclear(&(map->raw), free);
}

void	init_map(char *map_filepath)
{
	int		filde;

	if (vaildate_file_extension(map_filepath) == FT_ERROR)
	{
		printf("<error> Invalid file extension. Extension must be '.cub'.\n");
		return ;
	}
	filde = open(map_filepath, O_RDONLY);
	if (filde == FT_ERROR)
	{
		printf("<error> Failed to open file.\n");
		return ;
	}
	read_file(filde);
	printf("<info> Completed reading file.\n");
	if (parse_map() == FT_ERROR)
	{
		close(filde);
		exit_with_error("Failed to parse map.");
		return ;
	}
	clear_map_raw();
	print_map_data();
	printf("<info> Completed validating map.\n");
	close(filde);
}
