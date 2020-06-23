/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
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


int		check_intersection(t_filler *ptr, t_coords *player_coords)
{
	t_coords		*tmp;
	int				x;
	int				y;
	int				n;

	tmp = ptr->token_coords;
	n = 0;
	while (tmp)
	{
		x = player_coords->x + tmp->x;
		y = player_coords->y + tmp->y;
		if (x < 0 || y < 0 || x >= ptr->map_width || y >= ptr->map_height)
			return (-1);
		if (ptr->map[y][x] == ptr->enemy_char)
			return (-1);
		if (ptr->map[y][x] == ptr->player_char || ptr->map[y][x] == ft_tolower(ptr->player_char))
			n++;
		tmp = tmp->next;
	}
	return (n);
}

int		get_distance(t_filler *ptr, t_coords *player_coords)
{
	t_coords		*tmp;
	int				x;
	int				y;
	int				n;

	tmp = ptr->token_coords;
	n = 0;
	while (tmp)
	{
		x = player_coords->x + tmp->x;
		y = player_coords->y + tmp->y;
		n += ptr->heat_map[y][x];
		tmp = tmp->next;
	}
	return (n);
}

int		sum_heat_map_distances(t_filler *ptr)
{
	int		x;
	int		y;
	int		sum;

	sum = 0;
	y = 0;
	while (y < ptr->map_height)
	{
		x = 0;
		while (x < ptr->map_width)
		{
			sum += ptr->heat_map[y][x];
			x++;
		}
		y++;
	}
	return (sum);
}

int		solve(t_filler *ptr)
{
	t_coords	coords;
	int			dist;
	int			min;

	min = sum_heat_map_distances(ptr);
	coords.y = 0;
	while (coords.y < ptr->map_height)
	{
		coords.x = 0;
		while (coords.x < ptr->map_width)
		{
			if (check_intersection(ptr, &coords) == 1)
			{
				if ((dist = get_distance(ptr, &coords)) < min)
				{
					min = dist;
					ptr->x = coords.x - ptr->x_move;
					ptr->y = coords.y - ptr->y_move;
				}
			}
			coords.x++;
		}
		coords.y++;
	}
	ft_putnbr(ptr->y);
	write(1, " ", 1);
	ft_putnbr(ptr->x);
	write(1, "\n", 1);
	return (1);
}
