/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 11:42:27 by Alkor             #+#    #+#             */
/*   Updated: 2020/07/18 21:36:07 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "vis.h"
#include "libft.h"
#include "mlx.h"
#include <pthread.h>

void		error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

static void	cycle_body(t_visual *ptr, int h, int w)
{
	if ((h && h % ptr->len == 0) || (w && w % ptr->len == 0))
		put_pixel(ptr, w, h, BLACK);
	else if (ptr->filler->map[h / ptr->len][w / ptr->len] == 'O')
		put_pixel(ptr, w, h, BLUE);
	else if (ptr->filler->map[h / ptr->len][w / ptr->len] == 'o')
		put_pixel(ptr, w, h, CYAN);
	else if (ptr->filler->map[h / ptr->len][w / ptr->len] == 'X')
		put_pixel(ptr, w, h, RED);
	else if (ptr->filler->map[h / ptr->len][w / ptr->len] == 'x')
		put_pixel(ptr, w, h, ORANGE);
}

static void	*draw(void *pointer)
{
	int			h;
	int			w;
	t_visual	*ptr;

	ptr = (t_visual*)pointer;
	h = ptr->y_begin;
	while (h < ptr->y_end)
	{
		w = 0;
		while (w < ptr->w)
		{
			cycle_body(ptr, h, w);
			w++;
		}
		h++;
	}
	return (0);
}

int			thread(t_visual *ptr)
{
	int			result;
	pthread_t	threads[4];
	void		*status[4];
	int			i;
	t_visual	tmp[4];

	i = -1;
	while (++i < 4)
	{
		tmp[i] = *ptr;
		tmp[i].y_begin = i * (tmp[i].h / 4);
		tmp[i].y_end = tmp[i].y_begin + tmp[i].h / 4;
		if ((result = pthread_create(&threads[i], NULL, draw, &tmp[i])))
			error("Creating thread");
	}
	i = -1;
	while (++i < 4)
	{
		if ((result = pthread_join(threads[i], &status[i])))
			perror("Joining thread");
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 11, 31);
	return (0);
}
