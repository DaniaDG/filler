/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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


void	print_info(t_filler *ptr)
{
	fprintf(ptr->fd,
	"\n\t####################################################\n\
	####################    INFO    ####################\n\
	####################################################\n\n");
	fprintf(ptr->fd, "map h = %d, map w = %d, player char = %c, enemy char = %c\n",
					ptr->map_height, ptr->map_width, ptr->player_char, ptr->enemy_char);
	fprintf(ptr->fd, "MAP\n%s\n%s\n%s\n%s\n", ptr->map[7], ptr->map[8], ptr->map[9], ptr->map[12]);
	fprintf(ptr->fd, "token h = %d, token w = %d\n", ptr->token_height, ptr->token_width);
	t_coords	*list;
	list = ptr->token_coords;
	if (!list)
		fprintf(ptr->fd, "token coord list is empty\n");
	while (list)
	{
		fprintf(ptr->fd, "token coords (%d, %d)\n", list->x, list->y);
		list = list->next;
	}

	int		h;
	int		w;
	h = 0;
	fprintf(ptr->fd, "HEAT MAP\n");
	while (h < ptr->map_height)
	{
		w = 0;
		while (w < ptr->map_width)
		{
			fprintf(ptr->fd, "%2d ", ptr->heat_map[h][w]);
			w++;
		}
		fprintf(ptr->fd, "\n");
		h++;
	}

	fprintf(ptr->fd, "SOLUTION %d %d\n", ptr->y, ptr->x);

}


int		main()
{
	t_filler	*ptr;

	if (!(ptr = (t_filler*)malloc(sizeof(t_filler))))
		return (1);
	ptr->line = NULL;
	if (!get_info(ptr))
		close_program(ptr);
	while (1)
	{
		if (!init_maps(ptr))
			close_program(ptr);
		if (!fill_map(ptr))
			close_program(ptr);
		if (!get_token(ptr))
			close_program(ptr);
		if (!calc_heat_map(ptr))
			close_program(ptr);
		if (!solve(ptr))
			close_program(ptr);
		
		//free_all(ptr);
		// while (1)
		// 	continue;
	}
	close_program(ptr);
	return (0);
}
