/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 09:46:07 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/18 13:25:03 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"
#include "vis.h"

static void	error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

static void	get_len(t_visual *ptr)
{
	if (ft_max(ptr->filler->map_height, ptr->filler->map_width) < 25)
		ptr->len = 25;
	else if (ft_max(ptr->filler->map_height, ptr->filler->map_width) < 50)
		ptr->len = 20;
	else
		ptr->len = 7;
}

void		init_mlx(t_visual *ptr)
{
	get_len(ptr);
	ptr->h = ptr->len * ptr->filler->map_height;
	ptr->w = ptr->len * ptr->filler->map_width;
	if (!(ptr->mlx = mlx_init()))
		error("mlx init error");
	if (!(ptr->win = mlx_new_window(ptr->mlx, ptr->w + 20, ptr->h + 40,
					"Filler visualizer by bsausage")))
		error("windows init error");
	if (!(ptr->img = mlx_new_image(ptr->mlx, ptr->w, ptr->h)))
		error("image init error");
	ptr->data_addr = mlx_get_data_addr(ptr->img, &ptr->bits_per_pixel,
					&ptr->size_line, &ptr->endian);
	mlx_string_put(ptr->mlx, ptr->win, 5, 2, CYAN, "BLUE:");
	mlx_string_put(ptr->mlx, ptr->win, 150, 2, RED, "RED:");
}

t_visual	*init_ptr(void)
{
	t_visual	*ptr;

	if (!(ptr = (t_visual *)malloc(sizeof(t_visual))))
		error("init error");
	if (!(ptr->filler = (t_filler*)malloc(sizeof(t_filler))))
		return (NULL);
	init_values(ptr->filler);
	ptr->space = NOT_PRESSED;
	ptr->drawing_flag = IS_PRESSED;
	return (ptr);
}

void		draw_first_image(t_visual *ptr)
{
	int		h;
	int		w;

	h = 0;
	while (h < ptr->h)
	{
		w = 0;
		while (w < ptr->w)
		{
			if (h != 0 && h % ptr->len == 0)
				put_pixel(ptr, w, h, BLACK);
			else
			{
				if (w != 0 && w % ptr->len == 0)
					put_pixel(ptr, w, h, BLACK);
				else
					put_pixel(ptr, w, h, WHITE);
			}
			w++;
		}
		h++;
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 11, 31);
}
