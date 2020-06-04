/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 15:54:41 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/06 15:54:42 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p1;
	unsigned char	*p2;
	unsigned char	ch;

	ch = (unsigned char)c;
	p1 = (unsigned char*)dst;
	p2 = (unsigned char*)src;
	while (n--)
	{
		*p1 = *p2;
		if (*p1 == ch)
			return ((void*)(++p1));
		p1++;
		p2++;
	}
	return (NULL);
}
