/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/17 10:43:23 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"
#include <stdio.h>

void		get_player_name(t_filler *ptr, int flag)
{
	char	*tmp;
	int		i;

	i = 0;
	// if (!flag)
	// 	ptr->player_name = NULL;
	// else
	// 	ptr->enemy_name = NULL;
	while (ptr->line[i] != '\0')
	{
		if (ptr->line[i++] == '/')
			tmp = &ptr->line[i];
	}
	if (!flag)
		ptr->player_name = ft_strsub(tmp, 0, ft_strchr(tmp, '.') - tmp);
	else
		ptr->enemy_name = ft_strsub(tmp, 0, ft_strchr(tmp, '.') - tmp);
}

void		get_player_info(t_filler *ptr, int *flag)
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

static void	cycle_body(t_filler *ptr, int h, int w)
{
	if (ptr->map[h][w] == ptr->player_char ||
		ptr->map[h][w] == ft_tolower(ptr->player_char))
		add_coord_elem(&ptr->player_coords, w, h);
	if (ptr->map[h][w] == ptr->enemy_char ||
		ptr->map[h][w] == ft_tolower(ptr->enemy_char))
		add_coord_elem(&ptr->enemy_coords, w, h);
}

void	check_the_winner(t_filler *ptr)
{
	if (ft_strstr(ptr->line, "== O fin:"))
		ptr->o_point = ft_atoi(ptr->line + 10);
	if (ft_strstr(ptr->line, "== X fin:"))
		ptr->x_point = ft_atoi(ptr->line + 10);
}

int		fill_map(t_filler *ptr)
{
	int		h;
	int		w;
	int		gnl;

	h = 0;
	while ((gnl = get_next_line(0, &ptr->line)) > 0 && h < ptr->map_height)
	{
		w = 0;
		check_the_winner(ptr);
		if (ft_isdigit(*(ptr->line)) &&
			(int)ft_strlen(ptr->line) == ptr->map_width + 4)
		{
			ft_strncpy(ptr->map[h], ptr->line + 4, ptr->map_width);
			while (w < ptr->map_width)
			{
				cycle_body(ptr, h, w);
				w++;
			}
			h++;
		}
		ft_memdel((void**)&ptr->line);
	}
	return (gnl != 1 ? 0 : 1);
}

void	parse_token_str(t_filler *ptr, int h, int *flag)
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
