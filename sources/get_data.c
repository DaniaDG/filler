/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/02/12 09:18:37 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"
#include "get_next_line.h"
#include <stdio.h>

int			get_info(t_filler *ptr)
{
	char	*end;
	int		flag;

	flag = 0;
	while (get_next_line(0, &ptr->line) > 0)
	{
		fprintf(ptr->fd, "%s\n", ptr->line);		//for debug
		if (ft_strnequ(ptr->line, "$$$ exec p2", 11) && ft_strstr(ptr->line, "bsausage"))
		{
			ptr->player_char = 'X';
			ptr->enemy_char = 'O';
			flag = 1;
		}
		if (!flag)
		{
			ptr->player_char = 'O';
			ptr->enemy_char = 'X';
		}
		if (ft_strnequ(ptr->line, "Plateau", 7))
		{
			end = ptr->line + 7;
			ptr->map_height = ft_strtol(end, &end);
			ptr->map_width = ft_strtol(end, &end);
			return (1) ;
		}
		ft_memdel((void**)&ptr->line);
	}
	return (0);
}

int		fill_map(t_filler *ptr)
{
	int		h;
	int		w;

	h = 0;
	if (!(ft_strnequ(ptr->line, "Plateau", 7)))
		return (0);
	while (get_next_line(0, &ptr->line) > 0 && h < ptr->map_height)
	{
		fprintf(ptr->fd, "%s\n", ptr->line);		//for debug
		w = 0;
		if (ft_isdigit(*(ptr->line)))
		{
			ft_strncpy(ptr->map[h], ptr->line + 4, ptr->map_width);
			while (w < ptr->map_width)
			{
				if (ptr->map[h][w] == ptr->player_char || ptr->map[h][w] == ft_tolower(ptr->player_char))
					add_coord_elem(&ptr->player_coords, w, h);
				if (ptr->map[h][w] == ptr->enemy_char || ptr->map[h][w] == ft_tolower(ptr->enemy_char))
					add_coord_elem(&ptr->enemy_coords, w, h);
				w++;
			}
			h++;
		}
		ft_memdel((void**)&ptr->line);
	}
	return (1);
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
			add_coord_elem(&ptr->token_coords, w - ptr->x_move, h - ptr->y_move);
		w++;
	}
}

int			get_token(t_filler *ptr)
{
	char	*end;
	int		h;
	int		flag;
	//int		gnl;

	if (ptr->token_coords)
		free_coord_list(&ptr->token_coords);
	end = ptr->line + 5;
	ptr->token_height = ft_strtol(end, &end);
	ptr->token_width = ft_strtol(end, &end);
	fprintf(ptr->fd, "%s\n", ptr->line);		//for debug
	ft_memdel((void**)&ptr->line);
	h = 0;
	flag = 0;
	//ptr->line = (char*)malloc(sizeof(char) * (ptr->token_width + 1));
	while (h < ptr->token_height)
	{
		if (get_next_line(0, &ptr->line) <= 0)
			return (0);
		
		// if (h)
		// 	read(0, ptr->line, 1);
		// read(0, ptr->line, ptr->token_width);
		// ptr->line[ptr->token_width] = '\0';
		fprintf(ptr->fd, "token line [%s]\n", ptr->line);		//for debug
		parse_token_str(ptr, h, &flag);
		ft_memdel((void**)&ptr->line);
		h++;		
	}
	return (1);
}
