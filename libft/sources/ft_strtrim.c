/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:33:56 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/07 14:33:57 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*p;
	char	*ptr;

	if (!s)
		return (NULL);
	p = (char*)(s + ft_strlen(s) - 1);
	while (*s == '\n' || *s == '\t' || *s == ' ')
		s++;
	if (!(*s))
	{
		if (!(ptr = (char*)malloc(sizeof(char))))
			return (NULL);
		*ptr = '\0';
		return (ptr);
	}
	while (*p == '\n' || *p == '\t' || *p == ' ')
		p--;
	if (!(ptr = (char*)malloc(sizeof(char) * (p - s + 2))))
		return (NULL);
	ptr = ft_strncpy(ptr, s, p - s + 1);
	ptr[p - s + 1] = '\0';
	return (ptr);
}
