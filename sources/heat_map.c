/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/02/12 09:18:37 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"
#include <stdio.h>

void		calc_distance(t_filler *ptr, int ***map, int x, int y)
{
	int		**tmp;
	int		height;
	int		width;
	int		i;

	tmp = *map;
	i = ft_max(ptr->map_width, ptr->map_height) - 1;
	while (i >= 0)
	{
		height = y - i;
		while (height <= y + i)
		{
			width = x - i;
			while (width <= x + i)
			{
				if (height >= 0 && width >= 0 && height < ptr->map_height && width < ptr->map_width)
					tmp[height][width] = i;
				if (width == x + i)
					break ;
				width = (height == y - i || height == y + i) ? (width + 1) : (x + i);
			}
			height++;
		}
		i--;
	}
}


int			calc_heat_map(t_filler *ptr)
{
	t_coords	*enemy_coords;
	int			h;
	int			w;
	int			**tmp;

	if (!(tmp = init_int_tab(ptr->map_height, ptr->map_width)))
		return (0);
	if (!(enemy_coords = ptr->enemy_coords))
		return (0);
	calc_distance(ptr, &ptr->heat_map, enemy_coords->x, enemy_coords->y);
	enemy_coords = enemy_coords->next;
	while (enemy_coords)
	{
		calc_distance(ptr, &tmp, enemy_coords->x, enemy_coords->y);
		h = 0;
		while (h < ptr->map_height)
		{
			w = 0;
			while (w < ptr->map_width)
			{
				if (tmp[h][w] < ptr->heat_map[h][w])
					ptr->heat_map[h][w] = tmp[h][w];
				w++;
			}
			h++;
		}
		enemy_coords = enemy_coords->next;
	}
	free_int_tab(&tmp, ptr->map_height);
	return (1);
}

