/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_position.c                                    :+:      :+:    :+:   */
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

void	moove_token_coords(t_filler *ptr)
{
	t_token_coords	*tmp;

	tmp = ptr->token_coords;
	while (tmp)
	{
		ptr->x_move = tmp->x;
		ptr->y_move = tmp->y;
		tmp = tmp->next;
	}
	tmp = ptr->token_coords;
	while (tmp)
	{
		tmp->x -= ptr->x_move;
		tmp->y -= ptr->y_move;
		tmp = tmp->next;
	}
}

int		check_intersection(t_filler *ptr, t_coords player_shape)
{
	t_token_coords	*tmp;
	int				x;
	int				y;
	int				n;

	tmp = ptr->token_coords;
	n = 0;
	while (tmp)
	{
		x = player_shape.x + tmp->x;
		y = player_shape.y + tmp->y;
		if (x < 0 || y < 0 || x >= ptr->map_width || y >= ptr->map_height)
			return (-1);
		if (ptr->map[y][x] == 'X')
			return (-1);
		if (ptr->map[y][x] == 'o' || ptr->map[y][x] == 'O')
			n++;
		tmp = tmp->next;
	}
	return (n);
}

int		get_distance(t_filler *ptr, t_coords player_shape)
{
	t_token_coords	*tmp;
	int				x;
	int				y;
	int				n;

	tmp = ptr->token_coords;
	n = 0;
	while (tmp)
	{
		x = player_shape.x + tmp->x;
		y = player_shape.y + tmp->y;
		n += ptr->enemy_heat_map[y][x];
		tmp = tmp->next;
	}
	return (n);
}


int		find_position(t_filler *ptr)
{
	t_coords	*player_shape;
	int			dist;
	int			min;
	int			x;
	int			y;

	x = 0;
	y = 0;
	player_shape = ptr->player_shape;
	dist = 100000;
	min = dist;
	while (player_shape)
	{
		if (check_intersection(ptr, *player_shape) == 1)
		{
			if ((dist = get_distance(ptr, *player_shape)) < min)
			{
				min = dist;
				x = player_shape->x - ptr->x_move;
				y = player_shape->y - ptr->y_move;
			}
		}
		player_shape = player_shape->next;
	}
	printf("%d %d\n", y, x);
	return (0);
}
