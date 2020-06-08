/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
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

void        free_token(t_filler *ptr)
{
    int     height;
	char	*check;
	
    height = ptr->token_height - 1;
    while (height >= 0)
    {
		check = ptr->token[height];
        ft_memdel((void**)(&ptr->token[height]));
        height--;
    }
    //ft_memdel((void**)&ptr->token);
}

void	free_shape_list(t_filler *ptr)
{
	t_coords	*begin_list;
	int     	height;

	begin_list = ptr->player_shape;
	height = ptr->map_height - 1;
    while (height >= 0)
    {
        ft_memdel((void**)(&ptr->player_shape->heat_map[height]));
        height--;
    }
    ft_memdel((void**)&ptr->player_shape->heat_map);
	ptr->player_shape = ptr->player_shape->next;
	begin_list->next = NULL;
	ft_memdel((void**)&begin_list);
}

// void		free_all(t_filler *ptr)
// {
	
// }
