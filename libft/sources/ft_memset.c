/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:14:13 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/05 14:41:35 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t count)
{
	unsigned char	*str;
	unsigned char	c;

	c = (unsigned char)ch;
	str = (unsigned char*)buf;
	while (count--)
		*str++ = c;
	return (buf);
}
