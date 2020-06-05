/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/02/12 09:18:37 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef struct s_coords
{
	int				x;
	int				y;
	int				**heat_map;
	struct s_coords	*next;
}					t_coords;


typedef enum
{
	PLAYER_1,
	PLAYER_2
}					t_player;

typedef struct 		s_filler
{
	int				map_height;
	int				map_width;
	int				token_height;
	int				token_width;
	char			**map;
	//int				**heat_map;
	char			**token;
	t_coords		*shape;
	t_coords		*enemy_shape;
	t_player		player;
}					t_filler;


#endif
