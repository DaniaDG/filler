/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 12:48:04 by bsausage          #+#    #+#             */
/*   Updated: 2019/09/04 13:13:58 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if (!to_find[i])
		return ((char*)str);
	while (str[i])
	{
		while (str[i + k] == to_find[k])
		{
			if ((!str[i + k] && !to_find[k]))
				return ((char*)(str + i));
			k++;
		}
		if (!to_find[k])
			return ((char*)(str + i));
		i++;
		k = 0;
	}
	return (0);
}
