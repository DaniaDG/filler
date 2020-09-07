/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/19 10:46:45 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"

char	**init_char_tab(int height, int width)
{
	char	**tmp;
	int		h;

	h = 0;
	if (!(tmp = (char**)malloc(sizeof(char*) * (height + 1))))
		return (NULL);
	while (h < height)
	{
		if (!(tmp[h] = (char*)malloc(sizeof(char) * (width + 1))))
		{
			while (h-- <= 0)
				ft_memdel((void**)&tmp[h]);
			return (NULL);
			tmp[h][width] = '.';
		}
		h++;
	}
	tmp[h] = NULL;
	return (tmp);
}

int		**init_int_tab(int height, int width)
{
	int		**tmp;
	int		h;

	h = 0;
	if (!(tmp = (int**)malloc(sizeof(int*) * height)))
		return (NULL);
	while (h < height)
	{
		if (!(tmp[h] = (int*)malloc(sizeof(int) * width)))
		{
			while (h-- <= 0)
				ft_memdel((void**)&tmp[h]);
			return (NULL);
		}
		h++;
	}
	return (tmp);
}

void	init_values(t_filler *ptr)
{
	ptr->line = NULL;
	ptr->player_name = NULL;
	ptr->enemy_name = NULL;
	ptr->map = NULL;
	ptr->heat_map = NULL;
	ptr->token_coords = NULL;
	ptr->player_coords = NULL;
	ptr->enemy_coords = NULL;
	ptr->tmp_coords = ptr->enemy_coords;
	ptr->o_point = 0;
	ptr->x_point = 0;
	ptr->token_height = 0;
	ptr->token_width = 0;
	ptr->x_move = 0;
	ptr->y_move = 0;
	ptr->x = 0;
	ptr->y = 0;
	ptr->flag = 0;
	ptr->flag2 = 0;
}

int		init_maps(t_filler *ptr)
{
	if (!(ptr->map = init_char_tab(ptr->map_height, ptr->map_width)))
		return (0);
	if (!(ptr->heat_map = init_int_tab(ptr->map_height, ptr->map_width)))
		return (0);
	return (1);
}
