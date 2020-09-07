/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/19 10:46:22 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"

static void	calc_distance(t_filler *ptr, int ***map, int x, int y)
{
	int		h;
	int		w;
	int		i;

	i = ft_max(ptr->map_width, ptr->map_height) - 1;
	while (i >= 0)
	{
		h = y - i;
		while (h <= y + i)
		{
			w = x - i;
			while (w <= x + i)
			{
				if (h >= 0 && w >= 0 && h < ptr->map_height &&
										w < ptr->map_width)
					(*map)[h][w] = i;
				if (w == x + i)
					break ;
				w = (h == y - i || h == y + i) ? (w + 1) : (x + i);
			}
			h++;
		}
		i--;
	}
}

static void	cycle_body(t_filler *ptr, int **tmp)
{
	int		h;
	int		w;

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
}

int			calc_heat_map(t_filler *ptr)
{
	t_coords	*enemy_coords;
	int			**tmp;

	if (!(tmp = init_int_tab(ptr->map_height, ptr->map_width)))
		return (0);
	if (!(enemy_coords = ptr->enemy_coords))
		return (0);
	if (ptr->flag2 == 1)
	{
		calc_distance(ptr, &ptr->heat_map, enemy_coords->x, enemy_coords->y);
		enemy_coords = enemy_coords->next;
		ptr->flag2 = 2;
	}
	while (enemy_coords != ptr->tmp_coords->next)
	{
		calc_distance(ptr, &tmp, enemy_coords->x, enemy_coords->y);
		cycle_body(ptr, tmp);
		enemy_coords = enemy_coords->next;
	}
	free_int_tab(&tmp, ptr->map_height);
	return (1);
}
