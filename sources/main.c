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
	return (0);
}

char		**get_map(t_filler *ptr)
{
	char	**tmp;
	char	**res;
	char	*line;
	int		height;
	
	line = NULL;
	if (!(tmp = (char**)malloc(sizeof(char*) * (ptr->map_height + 1))))
		return (NULL);
	res = tmp;
	get_next_line(0, &line);
	//printf("test = %s\n", line);
	ft_memdel((void**)&line);
	height = 0;
	while (height < ptr->map_height)
	{
		get_next_line(0, &line);
		*tmp = ft_strdup(line + 4);
		ft_memdel((void**)&line);
		tmp++;
		height++;
	}
	*tmp = NULL;
	return (res);
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

t_coords	*create_coord_elem(int x, int y)
{
	t_coords	*tmp;

	if (!(tmp = (t_coords*)malloc(sizeof(t_coords))))
		return (NULL);
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;
	return (tmp);
}

int		add_coord(t_coords **begin_list, int x, int y)
{
	t_coords	*tmp;

	if (!(*begin_list))
		*begin_list = create_coord_elem(x, y);
	else
	{
		tmp = create_coord_elem(x, y);
		tmp->next = *begin_list;
		*begin_list = tmp;
	}
	return (0);
}

int		get_coords_enemy_shape(t_filler *ptr)
{
	int		x = 0;
	int		y = 0;

	while (y < ptr->map_width)
	{
		x = 0;
		while (x < ptr->map_height)
		{
			if (ptr->map[x][y] == 'X')
			{
				add_coord(&ptr->enemy_shape, x, y);
				//printf("x = %d, y = %d\n", x, y);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int		init_heat_map(t_filler *ptr)
{
	int		height = 0;

	if (!(ptr->heat_map = (int**)malloc(sizeof(int*) * ptr->map_height)))
		exit(1);
	while (height < ptr->map_height)
	{
		if (!(ptr->heat_map[height] = (int*)malloc(sizeof(int) * ptr->map_width)))
			exit (1);
		//printf("%d\n", ptr->heat_map[height][12]);
		height++;
	}
	return (0);
}

int		count_distance(t_filler *ptr, t_coords *enemy)
{
	int		x;
	int		y;

	y = 0;
	//printf("%d\n", ptr->heat_map[10][1]);
	while (y < ptr->map_height)
	{
		x = 0;
		while (x < ptr->map_width)
		{
			ptr->heat_map[x][y] = ft_abs(x - enemy->x) + ft_abs(y - enemy->y);
			printf("%d ", ptr->heat_map[x][y]);
			x++;
		}
		y++;
	}
	return (0);
}

int		make_heat_map(t_filler *ptr)
{
	t_coords	*tmp_enemy;

	init_heat_map(ptr);
	tmp_enemy = ptr->enemy_shape;
	// while (tmp_enemy)
	// {
	 	count_distance(ptr, tmp_enemy);
	// 	tmp_enemy = tmp_enemy->next;
	// }
	return (0);
}

void	print_heat_map(t_filler *ptr)
{
	int		x;
	int		y;

	printf("HEAT MAP\n");
	y = 0;
	while (y < ptr->map_height)
	{
		x = 0;
		while (x < ptr->map_width)
		{
			printf("%3d  ", ptr->heat_map[x][y]);
			x++;
		}
		printf("\n");
		y++;
	}
}

int		main()
{
	t_filler	*ptr;
	char		**map;

	if (!(ptr = (t_filler*)malloc(sizeof(t_filler))))
		return (0);
	get_map_size(ptr);
	ptr->map = get_map(ptr);
	get_token(ptr);
	map = ptr->map;
	get_coords_enemy_shape(ptr);
	make_heat_map(ptr);
	// while (*map)
	 //	printf("%s\n", *map++);
	// printf("map %d %d\n", ptr->map_height, ptr->map_width);
	// printf("token %d %d\n", ptr->token_height, ptr->token_width);
	// t_coords	*tmp = ptr->enemy_shape;
	// while (tmp)
	// {
	// 	printf("enemy shape (%d, %d)\n", tmp->x, tmp->y);
	// 	tmp = tmp->next;
	// }
	// print_heat_map(ptr);

	return (0);
}
