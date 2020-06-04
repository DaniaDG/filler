/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:35:26 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/06 18:36:07 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_by_zero(char t[4])
{
	t[0] = 0;
	t[1] = 0;
	t[2] = 0;
	t[3] = 0;
}

static int	convert(wchar_t c)
{
	int		i;
	char	t[4];

	i = 0;
	fill_by_zero(t);
	if (c < 0x800)
	{
		t[i++] = (char)(((c >> 6) & 0x1f) | 0xc0);
		t[i++] = (char)((c & 0x3f) | 0x80);
	}
	else if (c < 0x10000)
	{
		t[i++] = (char)(((c >> 12) & 0xf) | 0xe0);
		t[i++] = (char)(((c >> 6 & 0x3f)) | 0x80);
		t[i++] = (char)((c & 0x3f) | 0x80);
	}
	else
	{
		t[i++] = (char)(((c >> 18) & 0x7) | 0xf0);
		t[i++] = (char)(((c >> 12) & 0x3f) | 0x80);
		t[i++] = (char)(((c >> 6) & 0x3f) | 0x80);
		t[i++] = (char)((c & 0x3f) | 0x80);
	}
	write(1, t, i);
	return (i);
}

int			ft_putwchar(wchar_t c)
{
	char	t;

	if (c == 0)
	{
		t = (char)(c & 0x7f);
		write(1, &t, 0);
		return (0);
	}
	if (c < 0x80)
	{
		t = (char)(c & 0x7f);
		write(1, &t, 1);
	}
	return (convert(c));
}
