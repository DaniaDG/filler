/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

int		get_map_size(t_filler *ptr)
{
	char	*line;
	char	*end;

	while (get_next_line(0, &line))
	{
		if (ft_strnequ(line, "$$$ exec p1", 11))
			ptr->player = PLAYER_1;
		if (ft_strnequ(line, "$$$ exec p2", 11))
			ptr->player = PLAYER_2;
		if (ft_strnequ(line, "Plateau", 7))
		{
			end = line + 7;
			ptr->map_height = ft_strtol(end, &end);
			ptr->map_width = ft_strtol(end, &end);
			break ;
		}
		ft_memdel((void**)&line);
	}
	return (1);
}

char		**init_map(t_filler *ptr)
{
	char	**tmp;
	int		height;

	height = 0;
	if (!(tmp = (char**)malloc(sizeof(char*) * (ptr->map_height + 1))))
		return (NULL);
	while (height < ptr->map_height)
	{
		if (!(tmp[height] = (char*)malloc(sizeof(char) * (ptr->map_width + 1))))
		{
			while (height-- <= 0)
				ft_memdel((void**)&tmp[height]);
			return (NULL);
		}
		tmp[height][ptr->map_width] = '\0';
		height++;
	}
	tmp[height] = NULL;
	return (tmp);
}

void		get_map(t_filler *ptr)
{
	char	*line;
	int		height;
	
	line = NULL;
	while (get_next_line(0, &line))
	{
		if (*line == ' ')
		{
			ft_memdel((void**)&line);
			break ;
		}
		ft_memdel((void**)&line);
	}
	height = 0;
	while (height < ptr->map_height)
	{
		get_next_line(0, &line);
		ft_strncpy(ptr->map[height], line + 4, ptr->map_width);
		ft_memdel((void**)&line);
		height++;
	}
}

int		get_token(t_filler *ptr)
{
	char	**tmp;
	char	*line;
	char	*end;
	int		height;

	line = NULL;
	get_next_line(0, &line);
	end = line + 5;
	ptr->token_height = ft_strtol(end, &end);
	ptr->token_width = ft_strtol(end, &end);
	ft_memdel((void**)&line);
	if (!(tmp = (char**)malloc(sizeof(char*) * (ptr->token_height + 1))))
		return (0);
	ptr->token = tmp;
	height = 0;
	while (height < ptr->token_height)
	{
		get_next_line(0, &line);
		*tmp = ft_strdup(line);
		ft_memdel((void**)&line);
		tmp++;
		height++;
	}
	*tmp = NULL;
	return (1);
}


void		calculate_distance(t_filler *ptr, int ***map, int x, int y)
{
	int		**tmp;
	int		height;
	int		width;
	int		i;

	tmp = *map;
	i = ft_max(ptr->map_width, ptr->map_height) - 1;
	while (i >= 0)
	{
		height = y - i;
		while (height <= y + i)
		{
			width = x - i;
			while (width <= x + i)
			{
				if (height >= 0 && width >= 0 && height < ptr->map_height && width < ptr->map_width)
					tmp[height][width] = i;
				if (width == x + i)
					break ;
				width = (height == y - i || height == y + i) ? (width + 1) : (x + i);
			}
			height++;
		}
		i--;
	}
}

int			**init_heat_map(t_filler *ptr)
{
	int		**tmp;
	int		height;

	if (!(tmp = (int**)malloc(sizeof(int*) * ptr->map_height)))
		return (NULL);
	height = 0;
	while (height < ptr->map_height)
	{
		if (!(tmp[height] = (int*)malloc(sizeof(int) * ptr->map_width)))
		{
			while (height-- <= 0)
				ft_memdel((void**)&tmp[height]);
			return (NULL);
		}
		height++;
	}
	//calculate_distance(ptr, &tmp, x, y);
	return (tmp);
}


t_coords	*create_coord_elem(t_filler *ptr, int x, int y)
{
	t_coords	*tmp;

	if (!(tmp = (t_coords*)malloc(sizeof(t_coords))))
		return (NULL);
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;
	if (!(tmp->heat_map = init_heat_map(ptr)))
	{
		//free_list;
		return (NULL);
	}
	calculate_distance(ptr, &tmp->heat_map, x, y);
	return (tmp);
}

int		add_coord(t_filler *ptr, t_coords **begin_list, int x, int y)
{
	t_coords	*tmp;

	if (!(*begin_list))
	{
		if (!(*begin_list = create_coord_elem(ptr, x, y)))
			return (0);
	}
	else
	{
		if (!(tmp = create_coord_elem(ptr, x, y)))
			return (0);
		tmp->next = *begin_list;
		*begin_list = tmp;
	}
	return (1);
}

int		get_coords_enemy_shape(t_filler *ptr)
{
	int		x = 0;
	int		y = 0;

	while (y < ptr->map_height)
	{
		x = 0;
		while (x < ptr->map_width)
		{
			if (ptr->map[y][x] == 'X')
			{
				if (!(add_coord(ptr, &ptr->enemy_shape, x, y)))
					return (0);
			}
			if (ptr->map[y][x] == 'O' || ptr->map[y][x] == 'o')
			{
				if (!(add_coord(ptr, &ptr->player_shape, x, y)))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}


void	print_heat_map(t_filler *ptr, int **map)
{
	int		height;
	int		width;

	height = 0;
	while (height < ptr->map_height)
	{
		width = 0;
		while (width < ptr->map_width)
		{
			printf("%2d ", map[height][width]);
			width++;
		}
		printf("\n");
		height++;
	}
}

int		get_min_distance(t_filler *ptr, int height, int width, t_status status)
{
	t_coords	*list;
	int			min;

	list = status == ENEMY ? ptr->enemy_shape : ptr->player_shape;
	min = list->heat_map[height][width];
	while (list)
	{
		if (list->heat_map[height][width] < min)
			min = list->heat_map[height][width];
		list = list->next;
	}
	return (min);
}

void		make_heat_map(t_filler *ptr, t_status status)
{
	int			**tmp;
	int			height;
	int			width;

	tmp = status == PLAYER ? ptr->player_heat_map : ptr->enemy_heat_map;
	height = 0;
	while (height < ptr->map_height)
	{
		width = 0;
		while (width < ptr->map_width)
		{
			tmp[height][width] = get_min_distance(ptr, height, width, status);
			width++;
		}
		height++;
	}
}

int		add_token_coord(t_filler *ptr, int x, int y)
{
	t_token_coords	*tmp;

	if (!ptr->token_coords)
	{
		if (!(ptr->token_coords = (t_token_coords*)malloc(sizeof(t_token_coords))))
			return (0);
		ptr->token_coords->x = x;
		ptr->token_coords->y = y;
		ptr->token_coords->next = NULL;
	}
	else
	{
		if (!(tmp = (t_token_coords*)malloc(sizeof(t_token_coords))))
			return (0);
		tmp->x = x;
		tmp->y = y;
		tmp->next = ptr->token_coords;
		ptr->token_coords = tmp;
	}
	return (1);
}

int		get_token_coords(t_filler *ptr)
{
	int		height;
	int		width;

	height = 0;
	while (height < ptr->token_height)
	{
		width = 0;
		while (width < ptr->token_width)
		{
			if (ptr->token[height][width] == '*')
				add_token_coord(ptr, width, height);
			width++;
		}
		height++;
	}
	return (0);
}

int		main()
{
	t_filler	*ptr;

	if (!(ptr = (t_filler*)malloc(sizeof(t_filler))))
		return (0);
	if (!get_map_size(ptr))
		exit(1);
	if (!(ptr->map = init_map(ptr)))
		exit(1);
	if (!(ptr->enemy_heat_map = init_heat_map(ptr)))
		exit(1);
	if (!(ptr->player_heat_map = init_heat_map(ptr)))
		exit(1);

	//while (1) {
	get_map(ptr);	
	if (!get_token(ptr))
		exit(1);	
	get_token_coords(ptr);
	moove_token_coords(ptr);
	if (!get_coords_enemy_shape(ptr))
		exit(1);	
	make_heat_map(ptr, ENEMY);	
	make_heat_map(ptr, PLAYER);
	find_position(ptr);
	free_token(ptr);
	printf("%s %p\n", ptr->token[0], ptr->token[0]);
	printf("%s %p\n", ptr->token[1], ptr->token[1]);
	printf("%s %p\n", ptr->token[2], ptr->token[2]);
	printf("%s %p\n", ptr->token[3], ptr->token[3]);
	//free_shape_list(ptr);
	//}
	return (0);
}
