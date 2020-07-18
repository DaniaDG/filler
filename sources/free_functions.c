/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/18 12:30:04 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"
#include <stdio.h>

void		free_int_tab(int ***map, int height)
{
	int		h;
	int		**tmp;

	if (!*map)
		return ;
	tmp = *map;
	h = height - 1;
	while (h >= 0)
	{
		ft_memdel((void**)&tmp[h]);
		h--;
	}
	ft_memdel((void**)&tmp);
}

void		free_char_tab(char ***map, int height)
{
	int		h;
	char	**tmp;

	if (!*map)
		return ;
	tmp = *map;
	h = height;
	while (h >= 0)
	{
		ft_memdel((void**)&tmp[h]);
		h--;
	}
	ft_memdel((void**)&tmp);
}

void		free_lists(t_filler *ptr)
{
	free_coord_list(&ptr->player_coords);
	free_coord_list(&ptr->enemy_coords);
	ptr->player_coords = NULL;
	ptr->enemy_coords = NULL;
}

void		close_program(t_filler *ptr)
{
	free_coord_list(&ptr->token_coords);
	free_coord_list(&ptr->player_coords);
	free_coord_list(&ptr->enemy_coords);
	free_char_tab(&ptr->map, ptr->map_height);
	free_int_tab(&ptr->heat_map, ptr->map_height);
	ptr->map = NULL;
	ptr->heat_map = NULL;
	ft_memdel((void**)&ptr);
	exit(1);
}
