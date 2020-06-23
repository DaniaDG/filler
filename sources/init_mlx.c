/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 09:46:07 by bsausage          #+#    #+#             */
/*   Updated: 2019/10/22 09:07:49 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"
#include "viz.h"

static void	error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void		init_mlx(t_visual *ptr)
{
	if (!(ptr->mlx = mlx_init()))
		error("mlx init error");
	if (!(ptr->win = mlx_new_window(ptr->mlx, WIDTH, HEIGHT, "Filler visualizer by bsausage")))
		error("windows init error");
	if (!(ptr->img = mlx_new_image(ptr->mlx, IMG_W, IMG_H)))
		error("image init error");
	ptr->data_addr = mlx_get_data_addr(ptr->img, &(ptr->bits_per_pixel),
										&(ptr->size_line), &(ptr->endian));
}

t_visual	*init_ptr(void)
{
	t_visual	*ptr;

	if (!(ptr = (t_visual *)malloc(sizeof(t_visual))))
		error("init error");
	if (!(ptr->filler = (t_filler*)malloc(sizeof(t_filler))))
		return (NULL);
	ptr->filler->line = NULL;
	ptr->filler->map = NULL;
	init_mlx(ptr);
	return (ptr);
}
