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
#include "get_next_line.h"
#include <stdio.h>

int			main()
{
	char	*line = NULL;
	int		gnl;
	int		i = 0;

	while (i < 17)
	{
		gnl = get_next_line(0, &line);
		if (gnl == 0)
			break ;
		if (gnl == -1)
		{
			ft_putstr_fd("error\n", 2);
			exit(1);
		}
		ft_memdel((void**)&line);
		i++;
	}
	printf("8 2\n");
	while (i < 35)
	{
		gnl = get_next_line(0, &line);
		if (gnl == 0)
			break ;
		if (gnl == -1)
		{
			ft_putstr_fd("error\n", 2);
			exit(1);
		}
		ft_memdel((void**)&line);
		i++;
	}
	printf("8 8\n");
	return (0);
}
