/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alkor <Alkor@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:43:37 by Alkor             #+#    #+#             */
/*   Updated: 2020/07/18 21:51:26 by Alkor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include "filler.h"

# define RED			0xFF0000
# define CYAN			0x0088ff
# define ORANGE			0xff6a00
# define GREEN			0x00FF00
# define BLUE			0x0108D1
# define YELLOW			0xFFFDAC
# define GREY			0x555555
# define PINK			0xFF4DC4
# define SILVER			0xCCCCCC
# define WHITE			0xFFFFFF
# define BLACK			0x000000

typedef enum
{
	IS_PRESSED,
	NOT_PRESSED
}	t_button;

typedef struct			s_visual
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	int					len;
	int					h;
	int					w;
	t_button			space;
	t_button			drawing_flag;
	t_filler			*filler;
	int					y_begin;
	int					y_end;
}						t_visual;

t_visual				*init_ptr(void);
void					init_mlx(t_visual *ptr);
char					**init_xpm_image(t_filler *ptr, int len);
void					hooks(t_visual *ptr);
int						turn_off(void *param);
int						red(int rgb);
int						green(int rgb);
int						blue(int rgb);
int						rgb(int r, int g, int b);
int						color(int current, int max, int color1, int color2);
void					put_pixel(t_visual *ptr, int x, int y, int color);
void					background(t_visual *ptr, int color);
void					draw_first_image(t_visual *ptr);
int						thread(t_visual *ptr);

#endif
