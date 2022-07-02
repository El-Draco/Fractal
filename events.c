/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:09:10 by rriyas            #+#    #+#             */
/*   Updated: 2022/06/28 14:11:23 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int	key_hook(int keycode, t_render *var)
{
	if (keycode == 53)
	{
		mlx_destroy_window(var->all_vars.mlx, var->all_vars.win);
		exit(0);
	}
	else if (keycode == 49)
		var->img_data.col += 15;
	else if (keycode == 36)
		var->img_data.iter += 10;
	else if (keycode == 126)
		var->img_data.img_origin.y -= 0.5 * var->img_data.zoom;
	else if (keycode == 125)
		var->img_data.img_origin.y += 0.5 * var->img_data.zoom;
	else if (keycode == 123)
		var->img_data.img_origin.x -= 0.5 * var->img_data.zoom;
	else if (keycode == 124)
		var->img_data.img_origin.x += 0.5 * var->img_data.zoom;
	render_next_image(var);
	return (0);
}

int	my_mouse_hook(int keycode, int x, int y, t_render *var)
{
	int	l;
	int	w;

	l = var->img_data.l;
	w = var->img_data.w;
	if (keycode == 5)
	{
		var->img_data.zoom /= 1.25;
		var->img_data.img_origin.x += (x - l / 2) * var->img_data.zoom / (4 * l);
		var->img_data.img_origin.y
			+= (y - l / 2) * var->img_data.zoom / (4 * w);
	}
	if (keycode == 4)
	{
		var->img_data.zoom *= 1.25;
		var->img_data.img_origin.x
			+= (x - l / 2) / var->img_data.zoom * (4 / l);
		var->img_data.img_origin.y
			+= (y - l / 2) / var->img_data.zoom * (4 / w);
	}
	render_next_image(var);
	return (0);
}

int	my_close(t_render *vars)
{
	mlx_destroy_window(vars->all_vars.mlx, vars->all_vars.win);
	exit(0);
	return (0);
}
