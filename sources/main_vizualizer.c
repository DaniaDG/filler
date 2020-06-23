/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vizualizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/02/12 09:18:37 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"
#include "viz.h"

int		main()
{
	t_visual	*ptr;

	if (!(ptr = init_ptr()))
		return (0);
	if (!get_info(ptr->filler))
		exit (1);
	if (!init_maps(ptr->filler))
		exit(1);
	while (1)
	{
		if (!fill_map(ptr->filler))
			break ;
	}
	
	mlx_loop(ptr);
	return (0);
}
