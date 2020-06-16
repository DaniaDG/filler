/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
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

void		free_int_tab(int ***map, int height)
{
	int		h;
	int		**tmp;

	tmp = *map;
	h = height - 1;
	while (h >= 0)
	{
		ft_memdel((void**)&tmp[h]);
		h--;
	}
	ft_memdel((void**)&tmp);
}

void		free_char_tab(char ***map, int height)
{
	int		h;
	char	**tmp;

	tmp = *map;
	h = height;
	while (h >= 0)
	{
		ft_memdel((void**)&tmp[h]);
		h--;
	}
	ft_memdel((void**)&tmp);
}
