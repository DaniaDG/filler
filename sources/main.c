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
		//printf("test = %s\n", line);
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
	//printf("test = %s\n", line);
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

int			**init_heat_map(t_filler *ptr)
{
	int		**tmp;
	int		height;
	int		width;

	if (!(tmp = (int**)malloc(sizeof(int*) * ptr->map_height)))
		return (NULL);
	height = 0;
	while (height < ptr->map_height)
	{
		width = 0;
		if (!(tmp[height] = (int*)malloc(sizeof(int) * ptr->map_width)))
		{
			while (height-- <= 0)
				ft_memdel((void**)&tmp[height]);
			return (NULL);
		}
		while (width < ptr->map_width)
		{
			tmp[height][width] = 13;
			width++;
		}
		height++;
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
	if (!(tmp->heat_map = init_heat_map(ptr)))
	{
		//free_list;
		return (NULL);
	}
	return (tmp);
}

int		add_coord(t_filler *ptr, int x, int y)
{
	t_coords	*tmp;

	if (!(ptr->enemy_shape))
	{
		if (!(ptr->enemy_shape = create_coord_elem(ptr, x, y)))
			return (0);
	}
	else
	{
		if (!(tmp = create_coord_elem(ptr, x, y)))
			return (0);
		tmp->next = ptr->enemy_shape;
		ptr->enemy_shape = tmp;
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
				if (!(add_coord(ptr, x, y)))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	print_heat_map(t_filler *ptr)
{
	int		height;
	int		width;

	height = 0;
	while (height < ptr->map_height)
	{
		width = 0;
		while (width < ptr->map_width)
		{
			printf("%3d ", ptr->enemy_shape->heat_map[height][width]);
			width++;
		}
		write(1, "\n", 1);
		height++;
	}
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

	printf("x = %d, y = %d\n", ptr->map_width, ptr->map_height);

	if ((ptr->map = get_map(ptr)))
		printf("get_map OK\n");
	
	map = ptr->map;
	while (*map)
		printf("%s\n", *map++);

	if (get_token(ptr))
		printf("get_token OK\n");

	map = ptr->token;
	while (*map)
		printf("%s\n", *map++);

	if (get_coords_enemy_shape(ptr))
		printf("get_coords_enemy_shape OK\n");

	t_coords	*tmp = ptr->enemy_shape;
	while (tmp)
	{
		printf("enemy shape (%d, %d)\n", tmp->x, tmp->y);
		tmp = tmp->next;
	}
	// if (make_heat_map(ptr))
	// 	printf("make_heat_map OK\n");

	print_heat_map(ptr);

	// printf("map %d %d\n", ptr->map_height, ptr->map_width);
	// printf("token %d %d\n", ptr->token_height, ptr->token_width);
	


	return (0);
}
