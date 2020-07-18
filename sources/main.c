/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/17 23:10:18 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"

int		main(void)
{
	t_filler	*ptr;

	if (!(ptr = (t_filler*)malloc(sizeof(t_filler))))
		return (1);
	init_values(ptr);
	if (!get_info(ptr))
		close_program(ptr);
	if (!init_maps(ptr))
		close_program(ptr);
	while (1)
	{
		if (!fill_map(ptr))
			close_program(ptr);
		if (!get_token(ptr))
			close_program(ptr);
		if (!calc_heat_map(ptr))
			close_program(ptr);
		if (!solve(ptr))
			close_program(ptr);
		print_coords(ptr);
		free_lists(ptr);
	}
	return (0);
}
