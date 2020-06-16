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
	if (!(ptr->fd = fopen("/Users/Alkor/dania/filler/test", "a")))
		printf("Cannot open file.\n");
	fprintf(ptr->fd, "start\n");
	ptr->line = NULL;

	if (!get_info(ptr))
		return (0);
	if (!init_maps(ptr))
		return (0);
	if (!fill_map(ptr))
		return (0);
	if (!get_token(ptr))
		return (0);
	if (!calc_heat_map(ptr))
		return (0);
	if (!solve(ptr))
		return (0);

	//print_info(ptr);
	fclose(ptr->fd);
	return (0);
}



	// int		i = 0;
	// while (i < 15)
	// {
	// 	get_next_line(0, &ptr->line);
	// 	fprintf(ptr->fd, "%s\n", ptr->line);
	// 	ft_memdel((void**)&ptr->line);
	// 	i++;
	// }
	// printf("8 2\n");
	// i = 0;
	// while (i < 10)
	// {
	// 	get_next_line(0, &ptr->line);
	// 	fprintf(ptr->fd, "%s\n", ptr->line);
	// 	ft_memdel((void**)&ptr->line);
	// 	i++;
	// }
