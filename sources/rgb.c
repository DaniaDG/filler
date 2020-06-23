/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:25:25 by bsausage          #+#    #+#             */
/*   Updated: 2019/12/01 19:01:06 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viz.h"

int		red(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int		green(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int		blue(int rgb)
{
	return (rgb & 0xFF);
}

int		rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
