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

typedef struct 		s_coords
{
	int				x;
	int				y;
	int				**heat_map;
	struct s_coords	*next;
}					t_coords;

typedef struct 		s_tocken_coords
{
	int				x;
	int				y;
	struct s_tocken_coords	*next;
}					t_token_coords;

typedef enum
{
	PLAYER_1,
	PLAYER_2
}					t_player;

typedef enum
{
	PLAYER,
	ENEMY
}					t_status;

typedef struct 		s_filler
{
	int				map_height;
	int				map_width;
	int				token_height;
	int				token_width;
	char			**map;
	int				**enemy_heat_map;
	int				**player_heat_map;
	char			**token;
	t_token_coords	*token_coords;
	int				x_move;
	int				y_move;
	char			player_symbol;
	char			enemy_symbol;
	int				h_map[100][100];
	t_coords		*shape;
	t_coords		*enemy_shape;
	t_coords		*player_shape;
	t_player		player;
	t_status		status;
}					t_filler;


#endif
