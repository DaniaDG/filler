/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 14:34:08 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/07 14:34:09 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		words_nb(char const *s, char c)
{
	size_t n;

	n = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s)
		{
			n++;
			while (*s != c && *s)
				s++;
		}
	}
	return (n);
}

static size_t		word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s == c)
		s++;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static void			free_arr(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**arr_w;
	size_t			len;
	size_t			nb;
	size_t			i;

	if (!s)
		return (NULL);
	nb = words_nb(s, c);
	if (!(arr_w = (char**)malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	i = 0;
	while (i < nb)
	{
		while (*s == c)
			s++;
		len = word_len(s, c);
		if (!(arr_w[i++] = ft_strsub(s, 0, len)))
		{
			free_arr(arr_w, --i);
			return (NULL);
		}
		s = s + len;
	}
	arr_w[i] = NULL;
	return (arr_w);
}
