/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:55:01 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/04 15:35:44 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isascii(int ch)
{
	if (ch >= 0 && ch <= 127)
		return (1);
	else
		return (0);
}
