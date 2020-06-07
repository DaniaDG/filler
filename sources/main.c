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

char		**get_map(t_filler *ptr)
{
	char	**tmp;
	char	*line;
	int		height;
	
	line = NULL;
	if (!(tmp = (char**)malloc(sizeof(char*) * (ptr->map_height + 1))))
		return (NULL);
	get_next_line(0, &line);
	ft_memdel((void**)&line);
	height = 0;
	while (height < ptr->map_height)
	{
		get_next_line(0, &line);
		if (!(tmp[height] = ft_strdup(line + 4)))
		{
			while (height-- <= 0)
				ft_memdel((void**)&tmp[height]);
			return (NULL);
		}
		ft_memdel((void**)&line);
		height++;
	}
	tmp[height] = NULL;
	return (tmp);
}

int		get_token(t_filler *ptr)
{
	char	**tmp;
	char	*line;
	char	*end;
	int		height;

	line = NULL;
	get_next_line(0, &line);
	//printf("test = %s\n", line);
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


int			**init_heat_map(t_filler *ptr, int x, int y)
{
	int		**tmp;
	int		height;
	int		width;
	int		max;

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

	max = ft_max(ptr->map_width, ptr->map_height) - 1;
	while (max >= 0)
	{
		height = y - max;
		while (height <= y + max)
		{
			width = x - max;
			while (width <= x + max)
			{
				if (height >= 0 && width >= 0 && height < ptr->map_height && width < ptr->map_width)
					tmp[height][width] = max;
				if (width == x + max)
					break ;
				width = (height == y - max || height == y + max) ? (width + 1) : (x + max);
			}
			height++;
		}
		max--;
	}
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
	if (!(tmp->heat_map = init_heat_map(ptr, x, y)))
	{
		//free_list;
		return (NULL);
	}
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

int		**make_heat_map(t_filler *ptr, t_status status)
{
	int			**tmp;
	int			height;
	int			width;

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
		width = 0;
		while (width < ptr->map_width)
		{
			tmp[height][width] = get_min_distance(ptr, height, width, status);
			width++;
		}
		height++;
	}
	return (tmp);
}

// void	final_heat_map(t_filler *ptr)
// {
// 	int		h = 0;
// 	int		w = 0;

// 	while (h < ptr->map_height)
// 	{
// 		w = 0;
// 		while (w < ptr->map_width)
// 		{
// 			ptr->h_map[h][w] = ptr->player_heat_map[h][w] + ptr->enemy_heat_map[h][w];
// 			printf("%2d ", ptr->h_map[h][w]);
// 			w++;
// 		}
// 		printf("\n");
// 		h++;
// 	}
// }

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
	char		**map;

	if (!(ptr = (t_filler*)malloc(sizeof(t_filler))))
		return (0);
	ptr->enemy_shape = NULL;

	if (get_map_size(ptr))
		printf("get_map_size OK\n");

	printf("x = %d, y = %d\nPlayer's number %d\n", ptr->map_width, ptr->map_height,
													ptr->player == PLAYER_1 ? 1 : 2);

	if ((ptr->map = get_map(ptr)))
		printf("get_map OK\n");
	
	map = ptr->map;
	while (*map)
		printf("%s\n", *map++);

	if (get_token(ptr))
		printf("get_token OK\n");
	printf("x = %d, y = %d\n", ptr->token_width, ptr->token_height);
	map = ptr->token;
	while (*map)
		printf("%s\n", *map++);

	if (get_token_coords(ptr))
		printf("get_token coords OK\n");
	t_token_coords	*token;
	token = ptr->token_coords;
	while (token)
	{
		printf("token coords (%d, %d)\n", token->x, token->y);
		token = token->next;
	}

	if (get_coords_enemy_shape(ptr))
		printf("get_coords_enemy_shape OK\n");

	t_coords	*tmp = ptr->enemy_shape;
	while (tmp)
	{
		printf("enemy shape (%d, %d)\n", tmp->x, tmp->y);
		tmp = tmp->next;
	}

	tmp = ptr->player_shape;
	while (tmp)
	{
		printf("player shape (%d, %d)\n", tmp->x, tmp->y);
		tmp = tmp->next;
	}

	if ((ptr->enemy_heat_map = make_heat_map(ptr, ENEMY)))
		printf("make_heat_map ENEMY OK\n");

	print_heat_map(ptr, ptr->enemy_heat_map);
	printf("\n\n");

	if ((ptr->player_heat_map = make_heat_map(ptr, PLAYER)))
		printf("make_heat_map PLAYER OK\n");
	print_heat_map(ptr, ptr->player_heat_map);

	// final_heat_map(ptr);
	// printf("map %d %d\n", ptr->map_height, ptr->map_width);
	// printf("token %d %d\n", ptr->token_height, ptr->token_width);
	


	return (0);
}
