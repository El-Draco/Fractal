/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 08:50:04 by rriyas            #+#    #+#             */
/*   Updated: 2022/06/29 20:35:53 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	draw(t_render **data, t_coord *cart, t_coord pixel, int col)
{
	void	(*p[5])(t_render *data, t_coord *cart, t_coord pixel, int col);

	p[1] = plot_mandel;
	p[2] = plot_julia;
	p[3] = plot_burning_ship;
	p[4] = plot_newton;
	(*p[(*data)->type])(*data, cart, pixel, col);
}

void	plot_fractal(t_render *data, int L, int W)
{
	t_coord	quad4;
	t_coord	cart;
	int		col;
	int		i;
	int		j;

	col = data->img_data.col;
	i = 0;
	while (i < L)
	{
		quad4.x = i;
		j = 0;
		while (j < W)
		{
			quad4.y = j;
			cart = screen_to_cart(quad4, L, W);
			cart.x = data->img_data.img_origin.x + cart.x
				* data->img_data.zoom / L;
			cart.y = data->img_data.img_origin.y + cart.y
				* data->img_data.zoom / W;
			draw(&data, &cart, quad4, col);
			j++;
		}
		i++;
	}
}

int	render_next_image(t_render *data)
{
	// data->img_data.zoom *= 0.97;
	plot_fractal(data, data->img_data.l, data->img_data.w);
	mlx_put_image_to_window(data->all_vars.mlx, data->all_vars.win,
		data->img_data.img, 0, 0);
	return (0);
}

void	initialize(t_render *fract)
{
	fract->img_data.img_origin.x = 0;
	fract->img_data.img_origin.y = 0;
	fract->img_data.iter = 100;
	fract->img_data.zoom = 4;
	fract->img_data.shift_scale = 1;
	fract->img_data.l = 500;
	fract->img_data.w = 500;
	fract->all_vars.mlx = mlx_init();
	fract->all_vars.win = mlx_new_window(fract->all_vars.mlx,
			fract->img_data.l, fract->img_data.w, "Radi's Fractal :)");
	fract->img_data.img = mlx_new_image(fract->all_vars.mlx,
			fract->img_data.w, fract->img_data.w);
	fract->img_data.addr = mlx_get_data_addr(fract->img_data.img,
			&fract->img_data.bits_per_pixel,
			&fract->img_data.line_length, &fract->img_data.endian);
	fract->img_data.col = 25;
	if (fract->type == 1 || fract->type == 2)
		fract->img_data.col = 0x000000FF;
	else
		fract->img_data.col = 0x000000FF;
}

int	main(int argc, char **argv)
{
	t_render	fract;

	if (validate(argc, argv, &fract) == -1)
	{
		write(1, "Available fractals:\n./fractal 1\t\t\t(For Mandelbrot)\n", 52);
		write(1, "./fractal 2 real imaginary\t(For Julia)\n", 40 );
		write(1, "./fractal 3\t\t\t(For Burning Ship Fractal)\n", 42 );
		write(1, "./fractal 4\t\t\t(For Newton Fractal)\n", 36 );
		return (0);
	}
	initialize(&fract);
	render_next_image(&fract);
	mlx_key_hook(fract.all_vars.win, &key_hook, &fract);
	mlx_mouse_hook(fract.all_vars.win, &my_mouse_hook, &fract);
	mlx_hook(fract.all_vars.win, 17, 0, my_close, &fract);
	mlx_loop(fract.all_vars.mlx);
	return (0);
}
