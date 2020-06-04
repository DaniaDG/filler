/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:13:02 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/05 19:36:12 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*p1;
	char	*p2;

	if (!dst && !src)
		return (dst);
	p1 = (char*)dst;
	p2 = (char*)src;
	while (n-- > 0)
		*p1++ = *p2++;
	return (dst);
}
