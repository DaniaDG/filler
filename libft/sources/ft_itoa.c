/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:51:12 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/06 18:51:16 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_letters(int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = num_of_letters(n);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n == 0)
		str[0] = '0';
	if (str)
	{
		str[len--] = '\0';
		if (n < 0)
		{
			str[0] = '-';
			str[len--] = (n % 10) * (-1) + '0';
			n = (n / 10) * (-1);
		}
		while (n)
		{
			str[len--] = n % 10 + '0';
			n = n / 10;
		}
	}
	return (str);
}
