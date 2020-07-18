/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:15:55 by Alkor             #+#    #+#             */
/*   Updated: 2020/07/18 21:49:09 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"
#include "vis.h"

int				turn_off(void *param)
{
	(void)param;
	exit(0);
}

static void		winner_info(t_visual *ptr)
{
	char	*tmp;

	if (!(tmp = ft_itoa(ptr->filler->o_point)))
		return ;
	mlx_string_put(ptr->mlx, ptr->win, 65, 2, CYAN, tmp);
	ft_memdel((void**)&tmp);
	if (!(tmp = ft_itoa(ptr->filler->x_point)))
		return ;
	mlx_string_put(ptr->mlx, ptr->win, 200, 2, RED, tmp);
	ft_memdel((void**)&tmp);
}

static int		draw(t_visual *ptr)
{
	if (ptr->space == NOT_PRESSED)
		return (0);
	ft_memdel((void**)&ptr->filler->line);
	if (!(fill_map(ptr->filler)))
	{
		winner_info(ptr);
		ptr->space = NOT_PRESSED;
		ptr->drawing_flag = NOT_PRESSED;
		return (0);
	}
	thread(ptr);
	return (0);
}

static int		key_press(int key, t_visual *ptr)
{
	if (key == 53)
		turn_off(ptr);
	if (key == 49 && ptr->drawing_flag == IS_PRESSED)
	{
		ptr->space = ptr->space == NOT_PRESSED ? IS_PRESSED : NOT_PRESSED;
		mlx_loop_hook(ptr->mlx, &draw, ptr);
	}
	return (0);
}

void			hooks(t_visual *ptr)
{
	mlx_hook(ptr->win, 2, 0, key_press, ptr);
	mlx_hook(ptr->win, 17, 0, turn_off, ptr);
	mlx_loop(ptr->mlx);
}
