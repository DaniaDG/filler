/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vizualizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/18 13:24:51 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"
#include "vis.h"

int		main(void)
{
	t_visual	*ptr;

	if (!(ptr = init_ptr()))
		return (0);
	if (!get_info(ptr->filler))
		exit(1);
	init_mlx(ptr);
	if (!init_maps(ptr->filler))
		exit(1);
	draw_first_image(ptr);
	hooks(ptr);
	mlx_loop(ptr);
	return (0);
}
