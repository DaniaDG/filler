/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:30:09 by Alkor             #+#    #+#             */
/*   Updated: 2020/07/18 13:31:42 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"

static void	first_fill(t_filler *ptr, char *tmp, int h, int w)
{
	if (tmp[w] == ptr->player_char)
		add_coord_elem(&ptr->player_coords, w, h);
	if (tmp[w] == ptr->enemy_char && !ptr->flag2)
	{
		add_coord_elem(&ptr->enemy_coords, w, h);
		ptr->tmp_coords = ptr->enemy_coords;
		ptr->flag2 = 1;
	}
}

static void	cycle_body(t_filler *ptr, char *tmp, int h, int w)
{
	if (!ptr->flag)
	{
		first_fill(ptr, tmp, h, w);
		return ;
	}
	if ((tmp[w] == ft_tolower(ptr->player_char) ||
		tmp[w] == ptr->player_char) &&
		ptr->map[h][w] == '.')
		add_coord_elem(&ptr->player_coords, w, h);
	if ((tmp[w] == ft_tolower(ptr->enemy_char) ||
		tmp[w] == ptr->enemy_char) &&
		ptr->map[h][w] == '.')
		add_coord_elem(&ptr->enemy_coords, w, h);
}

static void	check_the_winner(t_filler *ptr)
{
	if (ft_strstr(ptr->line, "== O fin:"))
		ptr->o_point = ft_atoi(ptr->line + 10);
	if (ft_strstr(ptr->line, "== X fin:"))
		ptr->x_point = ft_atoi(ptr->line + 10);
}

int			fill_map(t_filler *ptr)
{
	int		h;
	int		w;
	int		gnl;

	h = 0;
	ptr->tmp_coords = ptr->enemy_coords;
	while ((gnl = get_next_line(0, &ptr->line)) > 0 && h < ptr->map_height)
	{
		w = 0;
		check_the_winner(ptr);
		if (ft_isdigit(*(ptr->line)) &&
			(int)ft_strlen(ptr->line) == ptr->map_width + 4)
		{
			while (w < ptr->map_width)
				cycle_body(ptr, ptr->line + 4, h, w++);
			ft_strncpy(ptr->map[h], ptr->line + 4, ptr->map_width);
			h++;
			if (h == ptr->map_height)
				ptr->flag = 1;
		}
		ft_memdel((void**)&ptr->line);
	}
	return (gnl != 1 ? 0 : 1);
}
