/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vizualizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/18 12:35:19 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"
#include "vis.h"

int		turn_off(void *param)
{
	(void)param;
	exit(0);
}

void	winner_info(t_visual *ptr)
{
	char	*tmp;

	if (!(tmp = ft_itoa(ptr->filler->o_point)))
		return ;
	mlx_string_put(ptr->mlx, ptr->win, 65, 2, CYAN, tmp);
	ft_memdel((void**)&tmp);
	if (!(tmp = ft_itoa(ptr->filler->x_point)))
		return ;
	mlx_string_put(ptr->mlx, ptr->win, 200, 2, RED, tmp);
}

int		draw(t_visual *ptr)
{
	if (ptr->space == NOT_PRESSED)
		return (0);
	free_lists(ptr->filler);
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

int		key_press(int key, t_visual *ptr)
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

void	hooks(t_visual *ptr)
{
	mlx_hook(ptr->win, 2, 0, key_press, ptr);
	mlx_hook(ptr->win, 17, 0, turn_off, ptr);
	mlx_loop(ptr->mlx);
}

void	get_len(t_visual *ptr)
{
	if (ft_max(ptr->filler->map_height, ptr->filler->map_width) < 25)
		ptr->len = 25;
	else if (ft_max(ptr->filler->map_height, ptr->filler->map_width) < 50)
		ptr->len = 20;
	else
		ptr->len = 7;
}

int		main(void)
{
	t_visual	*ptr;

	if (!(ptr = init_ptr()))
		return (0);
	if (!get_info(ptr->filler))
		exit(1);
	get_len(ptr);
	init_mlx(ptr);
	if (!init_maps(ptr->filler))
		exit(1);
	color_first_image(ptr);
	hooks(ptr);
	mlx_loop(ptr);
	return (0);
}
