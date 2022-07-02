/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:05:32 by rriyas            #+#    #+#             */
/*   Updated: 2022/06/19 14:13:22 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include "minilibx_opengl_20191021/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

typedef struct s_coord
{
	double	x;
	double	y;
}			t_coord;

typedef struct s_data
{
	int		iter;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	zoom;
	double	shift_scale;
	t_coord	img_origin;
	int		l;
	int		w;
	int		col;
}			t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}			t_vars;

typedef enum types{
	MANDELOBROT = 1,
	JULIA		= 2,
	BONUS		= 3
}t_fractal;

typedef struct s_render
{
	t_vars		all_vars;
	t_data		img_data;
	t_coord		cursor;
	t_fractal	type;
	t_coord		c;
}				t_render;

//events.c

int		key_hook(int keycode, t_render *var);
int		my_mouse_hook(int keycode, int x, int y, t_render *var);
int		my_close(t_render *vars);

//fractal_utils.c:
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_coord	screen_to_cart(t_coord cart, int L, int W);
int		is_num(char *s);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_atoi(const char *nptr);

//fractal.c:
int		col_picker(double continuous_index, int col);
void	plot_mandel(t_render *data, t_coord *cart, t_coord pixel, int col);
void	plot_julia(t_render *data, t_coord *cart, t_coord pixel, int col);
void	plot_burning_ship(t_render *data, t_coord *cart, t_coord pixel,
			int col);
void	plot_newton(t_render *data, t_coord *cart, t_coord pixel, int col);

//parse.c:
double	float_parser(char *s);
int		white_space(char ch);
int		extra_chars(char *str);
int		find_invalid_chars(char **argv);
int		validate(int argc, char **argv, t_render *f);

//main.c:
void	draw(t_render **data, t_coord *cart, t_coord pixel, int col);
void	plot_fractal(t_render *data, int L, int W);
int		render_next_image(t_render *data);
void	initialize(t_render *fract);
#endif
