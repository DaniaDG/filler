/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/14 09:20:07 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"
#include <stdio.h>

t_coords		*create_coord_elem(int x, int y)
{
	t_coords	*elem;

	if (!(elem = (t_coords*)malloc(sizeof(t_coords))))
		return (NULL);
	elem->x = x;
	elem->y = y;
	elem->next = NULL;
	return (elem);
}

void			add_coord_elem(t_coords **begin, int x, int y)
{
	t_coords	*tmp;

	if (!(tmp = create_coord_elem(x, y)))
	{
		free_coord_list(begin);
		return ;
	}
	if (!(*begin))
		*begin = tmp;
	else
	{
		tmp->next = *begin;
		*begin = tmp;
	}
}

void			free_coord_list(t_coords **begin)
{
	t_coords	*tmp;

	while (*begin)
	{
		tmp = *begin;
		*begin = (*begin)->next;
		tmp->next = NULL;
		ft_memdel((void**)&tmp);
	}
}
