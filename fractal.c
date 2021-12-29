#include "mlx.h"
#include "fractal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_coord
{
	double x;
	double y;
} t_coord;

typedef struct s_data
{
	int iter;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int scale;
} t_data;

typedef struct s_vars
{
	void *mlx;
	void *win;
} t_vars;

typedef struct s_render
{
	t_vars all_vars;
	t_data img_data;
} t_render;

const int L = 1920;
const int W = 1080;

// struct colors

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_coord change_system(t_coord cart)
{
	cart.x = cart.x - L / 2;
	cart.y = cart.y - W / 2;
	return cart;
}

int key_hook(int keycode, t_render *var)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 36)
	{
		var->img_data.iter += 10;
	}
	else if (keycode == 126)
	{
		var->img_data.scale /= 2;
		printf("%d", var->img_data.scale);
	}
	else if (keycode == 125)
		var->img_data.scale *= 2;
	// vars->iter += 10;
	return 0;
}

int my_mouse_hook(int keycode, int x, int y, t_render *var)
{
	if (keycode == 4)
	{
		var->img_data.scale *= 2;
	}
	if (keycode == 5)
		var->img_data.scale /= 2;

	return 0;
}

// t_data *img, t_vars *var;
void mandelbrot(t_data *img)
{
	int iter;

	iter = 0;
	t_coord quad4;
	t_coord cart;
	double x, y, temp;
	int flag = 0;
	int col = 0x00FF8000;
	// int col = 0x00D7AFD7;
	int bg = col;
	for (int i = 0; i < L; i++)
	{
		quad4.x = i;
		for (int j = 0; j < W; j++)
		{
			quad4.y = j;
			cart = change_system(quad4);
			cart.x = cart.x * img->scale / W;
			cart.y = cart.y * img->scale / W;
			x = 0;
			y = 0;
			iter = 0;
			while (x * x + y * y <= 4 && iter < img->iter)
			{
				temp = x * x - y * y + cart.x;
				y = 2 * x * y + cart.y;
				x = temp;
				iter++;
			}
			if (iter < img->iter)
				my_mlx_pixel_put(img, i, j, col * iter * 10);
			else
				my_mlx_pixel_put(img, i, j, bg);
		}
	}
}

int render_next_image(t_render *data)
{
	// mlx_mouse_hide();
	mandelbrot(&(data->img_data));
	mlx_put_image_to_window(data->all_vars.mlx, data->all_vars.win, data->img_data.img, 0, 0);
	return 0;
}

int main(int argc, char **argv)
{
	// void *mlx_ptr;
	// void *mlx_win;
	// t_vars vars;
	// t_data img; // to hold image data
	static t_render fract;
	if (argc != 2)
	{
		printf("Usage ./fractal [fractal]\nAvailabe sets: \n1. Mandelbrot\n2. Julia\n.");
		return 0;
	}
	fract.img_data.iter = 2;
	fract.img_data.scale = 4;
	fract.all_vars.mlx = mlx_init();
	fract.all_vars.win = mlx_new_window(fract.all_vars.mlx, L, W, "Radi's Fractal :)");
	fract.img_data.img = mlx_new_image(fract.all_vars.mlx, L, W);
	fract.img_data.addr = mlx_get_data_addr(fract.img_data.img, &fract.img_data.bits_per_pixel, &fract.img_data.line_length, &fract.img_data.endian);


	mlx_key_hook(fract.all_vars.win, &key_hook, &fract);
	mlx_mouse_hook(fract.all_vars.win, &my_mouse_hook, &fract);
	mlx_loop_hook(fract.all_vars.mlx, &render_next_image, &fract);
	mlx_loop(fract.all_vars.mlx);
}
// gcc -I ~/Desktop/minilibx fractal.c -L ~/Desktop/minilibx -lmlx -framework OpenGL -framework AppKit && ./a.out
// col * rgb_to_int(fabs(sin(i*j))*i*j,i+j,i-j)
