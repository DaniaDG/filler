/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viz.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsausage <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:18:37 by bsausage          #+#    #+#             */
/*   Updated: 2020/02/12 09:18:37 by bsausage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIZ_H
# define VIZ_H

# include "filler.h"

# define IMG_H			500
# define IMG_W			1000
# define HEIGHT			550
# define WIDTH			1000

# define RED			0xFF0000
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
}						t_button;

typedef struct			s_visual
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_filler			*filler;
}						t_visual;

t_visual				*init_ptr(void);
void					init_mlx(t_visual *ptr);
int						red(int rgb);
int						green(int rgb);
int						blue(int rgb);
int						rgb(int r, int g, int b);
int						color(int current, int max, int color1, int color2);
void					put_pixel(t_visual *ptr, int x, int y, int color);


#endif
