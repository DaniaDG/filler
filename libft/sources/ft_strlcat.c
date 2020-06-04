/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:47:30 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/06 13:47:32 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t lensrc;
	size_t lendest;

	lensrc = ft_strlen(src);
	lendest = ft_strlen(dest);
	if (lendest > size)
		lendest = size;
	if (lendest == size)
		return (size + lensrc);
	if (lensrc < size - lendest)
		ft_memcpy(dest + lendest, src, lensrc + 1);
	else
	{
		ft_memcpy(dest + lendest, src, size - lendest - 1);
		dest[size - 1] = '\0';
	}
	return (lendest + lensrc);
}
