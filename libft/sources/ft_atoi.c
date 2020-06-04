/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:24:19 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/03 19:26:09 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		check_overlong(unsigned long *n, int *sign)
{
	unsigned long max;

	max = 9223372036854775807;
	if (*n > max && *sign > 0)
	{
		*n = 1;
		*sign = -1;
	}
	if ((*n > max + 1) && *sign < 0)
		*n = 0;
}

int				ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	check_overlong(&result, &sign);
	return ((int)result * sign);
}
