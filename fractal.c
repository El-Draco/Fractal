/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:05:35 by rriyas            #+#    #+#             */
/*   Updated: 2022/06/28 14:22:26 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	col_picker(double continuous_index, int col)
{
	int	r;
	int	g;
	int	b;

	r = (unsigned char)(sin(0.069 * continuous_index + 4) * 230 + col);
	g = (unsigned char)(sin(0.069 * continuous_index + 2) * 230 + col);
	b = (unsigned char)(sin(0.069 * continuous_index + 1) * 230 + col);
	return ((r << 16) | (g << 8) | b);
}

void	plot_mandel(t_render *data, t_coord *cart, t_coord pixel, int col)
{
	double	x;
	double	y;
	double	temp;
	int		iter;
	double	cont;

	iter = 0;
	x = 0;
	y = 0;
	while (x * x + y * y <= 4 && iter < data->img_data.iter)
	{
		temp = x * x - y * y + cart->x;
		y = 2 * x * y + cart->y;
		x = temp;
		iter++;
	}
	cont = iter + 10 - (log(2)
			/ fabs(sqrt(cart->x * cart->x + cart->y * cart->y))) / log (2);
	col = col_picker(cont, col);
	if (iter < data->img_data.iter)
		my_mlx_pixel_put(&data->img_data, pixel.x, pixel.y, col);
	else
		my_mlx_pixel_put(&data->img_data, pixel.x, pixel.y, 0x0);
}

void	plot_burning_ship(t_render *data, t_coord *cart, t_coord pixel, int col)
{
	double	temp;
	int		iter;
	double	x;
	double	y;
	double	cont;

	iter = 0;
	x = 0;
	y = 0;
	while (x * x + y * y <= 4 && iter < data->img_data.iter)
	{
		temp = x * x - y * y + cart->x;
		y = fabs(2 * x * y) + cart->y;
		x = temp;
		iter++;
	}
	cont = iter + 10 - (log(2)
			/ fabs(sqrt(cart->x * cart->x + cart->y * cart->y))) / log (2);
	col = col_picker(cont, col);
	if (iter < data->img_data.iter)
		my_mlx_pixel_put(&data->img_data, pixel.x, pixel.y, col);
	else
		my_mlx_pixel_put(&data->img_data, pixel.x, pixel.y, 0x0);
}

void	plot_julia(t_render *data, t_coord *cart, t_coord pixel, int col)
{
	double	temp;
	int		iter;
	double	mx;
	double	my;
	int		max_iter;

	mx = data->c.x;
	my = data->c.y;
	max_iter = data->img_data.iter;
	iter = 0;
	while (cart->x * cart->x + cart->y * cart->y <= 4 && iter < max_iter)
	{
		temp = cart->x * cart->x - cart->y * cart->y + mx;
		cart->y = 2 * cart->x * cart->y + my;
		cart->x = temp;
		iter++;
	}
	temp = iter + 10 - (log(2)
			/ fabs(sqrt(cart->x * cart->x + cart->y * cart->y))) / log (2);
	col = col_picker(temp, col);
	if (iter < data->img_data.iter)
		my_mlx_pixel_put(&data->img_data, pixel.x, pixel.y, col);
	else
		my_mlx_pixel_put(&data->img_data, pixel.x, pixel.y, 0x0);
}

void	plot_newton(t_render *data, t_coord *cart, t_coord pixel, int col)
{
	double	temp;
	int		iter;
	double	old_x;
	double	old_y;
	double	cont;

	iter = 0;
	temp = 1.0f;
	while (temp > 0.001 && iter < data->img_data.iter)
	{
		old_x = cart->x;
		old_y = cart->y;
		temp = (cart->x * cart->x + cart->y * cart->y)
			* (cart->x * cart->x + cart->y * cart->y);
		cart->x = (2 * cart->x * temp + cart->x * cart->x - cart->y * cart->y)
			/ (3.0 * temp);
		cart->y = (2 * cart->y * (temp - old_x)) / (3.0 * temp);
		temp = (cart->x - old_x) * (cart->x - old_x)
			+ (cart->y - old_y) * (cart->y - old_y);
		iter++;
	}
	cont = iter + 10 - (log(2)
			/ fabs(sqrt(cart->x * cart->x + cart->y * cart->y))) / log (2);
	col = col_picker(cont, col);
	my_mlx_pixel_put(&data->img_data, pixel.x, pixel.y, col);
}
