/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:33:33 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/07 14:33:34 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*result;

	if (!s)
		return (NULL);
	if (!(ptr = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result = ptr;
	while (len--)
		*ptr++ = *(s + start++);
	*ptr = '\0';
	return (result);
}
