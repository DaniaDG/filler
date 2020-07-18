/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:29:53 by Alkor             #+#    #+#             */
/*   Updated: 2020/07/18 20:37:15 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"

static void	get_player_info(t_filler *ptr, int *flag)
{
	if (ft_strnequ(ptr->line, "$$$ exec p2", 11) &&
		ft_strstr(ptr->line, "bsausage"))
	{
		ptr->player_char = 'X';
		ptr->enemy_char = 'O';
		*flag = 1;
	}
	if (!*flag)
	{
		ptr->player_char = 'O';
		ptr->enemy_char = 'X';
	}
}

int			get_info(t_filler *ptr)
{
	char	*end;
	int		flag;
	int		gnl;

	flag = 0;
	while ((gnl = get_next_line(0, &ptr->line)) > 0)
	{
		if (gnl != 1)
			return (0);
		get_player_info(ptr, &flag);
		if (ft_strnequ(ptr->line, "Plateau", 7))
		{
			end = ptr->line + 7;
			ptr->map_height = ft_strtol(end, &end);
			ptr->map_width = ft_strtol(end, &end);
			ft_memdel((void**)&ptr->line);
			return (1);
		}
		ft_memdel((void**)&ptr->line);
	}
	return (0);
}

static void	parse_token_str(t_filler *ptr, int h, int *flag)
{
	int		w;

	w = 0;
	while (w < ptr->token_width)
	{
		if (ptr->line[w] == '*' && !*flag)
		{
			ptr->x_move = w;
			ptr->y_move = h;
			*flag = 1;
		}
		if (ptr->line[w] == '*')
			add_coord_elem(&ptr->token_coords,
							w - ptr->x_move, h - ptr->y_move);
		w++;
	}
}

int			get_token(t_filler *ptr)
{
	char	*end;
	int		h;
	int		flag;

	end = ptr->line + 5;
	ptr->token_height = ft_strtol(end, &end);
	ptr->token_width = ft_strtol(end, &end);
	ft_memdel((void**)&ptr->line);
	h = 0;
	flag = 0;
	while (h < ptr->token_height)
	{
		if (get_next_line(0, &ptr->line) <= 0)
			return (0);
		parse_token_str(ptr, h, &flag);
		ft_memdel((void**)&ptr->line);
		h++;
	}
	return (1);
}
