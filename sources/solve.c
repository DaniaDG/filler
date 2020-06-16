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


int		solve(t_filler *ptr)
{
	t_coords	*player_coords;
	int			dist;
	int			min;
	int			flag;

	flag = 0;
	player_coords = ptr->player_coords;
	while (player_coords)
	{
		if (check_intersection(ptr, player_coords) == 1)
		{
			dist = get_distance(ptr, player_coords);
			min = dist;
			ptr->x = player_coords->x - ptr->x_move;
			ptr->y = player_coords->y - ptr->y_move;
			player_coords = player_coords->next;
			flag = 1;
			break ;
		}
		player_coords = player_coords->next;
	}
	if (!flag)
		return (0);
	while (player_coords)
	{
		if (check_intersection(ptr, player_coords) == 1)
		{
			if ((dist = get_distance(ptr, player_coords)) < min)
			{
				min = dist;
				ptr->x = player_coords->x - ptr->x_move;
				ptr->y = player_coords->y - ptr->y_move;
			}
		}
		player_coords = player_coords->next;
	}
	printf("%d %d\n", ptr->y, ptr->x);
	return (1);
}
