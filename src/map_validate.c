/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:16:53 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/31 13:44:37 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(void)
{
	if (check_map_characters() == FT_ERROR)
	{
		printf("<TEST> check_map_characters\n");
		return (FT_ERROR);
	}
	if (check_map_walls() == FT_ERROR)
	{
		printf("<TEST> check_map_walls\n");
		return (FT_ERROR);
	}
	if (check_map_required_characters() == FT_ERROR)
	{
		printf("<TEST> check_map_required_characters\n");
		return (FT_ERROR);
	}
	return (FT_SUCCESS);
}
