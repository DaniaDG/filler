/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:41:18 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/06 12:50:45 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t i;
	size_t k;

	i = 0;
	k = 0;
	if (!to_find[i])
		return ((char*)str);
	while (str[i] && i < n)
	{
		while (str[i + k] == to_find[k] && (i + k) < n)
		{
			if ((!str[i + k] && !to_find[k]))
				return ((char*)(str + i));
			k++;
		}
		if (!to_find[k])
			return ((char*)(str + i));
		i++;
		k = 0;
	}
	return (0);
}
