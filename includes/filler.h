/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/07/18 10:08:13 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef struct			s_coords
{
	int					x;
	int					y;
	struct s_coords		*next;
}						t_coords;

typedef struct			s_filler
{
	char				*line;
	int					o_point;
	int					x_point;
	int					map_height;
	int					map_width;
	int					token_height;
	int					token_width;
	char				player_char;
	char				enemy_char;
	char				*player_name;
	char				*enemy_name;
	char				**map;
	int					**heat_map;
	t_coords			*token_coords;
	t_coords			*player_coords;
	t_coords			*enemy_coords;
	t_coords			*tmp_coords;
	int					flag2;
	int					x_move;
	int					y_move;
	int					x;
	int					y;
	int					flag;
}						t_filler;

void					init_values(t_filler *ptr);
int						init_maps(t_filler *ptr);
int						**init_int_tab(int height, int width);
int						get_info(t_filler *ptr);
int						get_data(t_filler *ptr);
int						fill_map(t_filler *ptr);
void					add_coord_elem(t_coords **begin, int x, int y);
int						calc_heat_map(t_filler *ptr);
int						get_token(t_filler *ptr);
int						check_intersection(t_filler *ptr, t_coords *player_coords);
int						solve(t_filler *ptr);
void					print_coords(t_filler *ptr);
void					free_lists(t_filler *ptr);
void					free_coord_list(t_coords **begin);
void					free_int_tab(int ***map, int height);
void					free_char_tab(char ***map, int height);
void					close_program(t_filler *ptr);

#endif
