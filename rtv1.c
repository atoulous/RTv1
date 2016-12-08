/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:06:17 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/08 19:48:46 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	fill_image(t_ray *ray, int color, double angle)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (angle >= 0.15 && angle < 1)
	{
		r = (color & 0xFF) * angle;
		g = ((color & 0xFF00) >> 8) * angle;
		b = ((color & 0xFF0000) >> 16) * angle;
	}
	else
	{
		r = (color & 0xFF) * 0.15;
		g = ((color & 0xFF00) >> 8) * 0.15;
		b = ((color & 0xFF0000) >> 16) * 0.15;
	}
	if (angle >= 0.990000 && angle < 1)
	{
		r += (255 - r) * (angle - 0.99) / 0.01;
		g += (255 - g) * (angle - 0.99) / 0.01;
		b += (255 - b) * (angle - 0.99) / 0.01;
	}
	ray->DATA[Y * ray->SIZELINE + X * (ray->BPP / 8)] = r;
	ray->DATA[Y * ray->SIZELINE + X * (ray->BPP / 8) + 1] = g;
	ray->DATA[Y * ray->SIZELINE + X * (ray->BPP / 8) + 2] = b;
}

void	init_variables(t_var *var)
{
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, WIDTH_WIN, HEIGHT_WIN, SCENE_NAME);
	IMG = mlx_new_image(MLX, WIDTH_WIN, HEIGHT_WIN);
	DATA = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	TH = -1;
	while (++TH < NB_TH)
	{
		if (!(var->ray[TH] = (t_ray *)ft_memalloc(sizeof(t_ray))))
			exit(EXIT_FAILURE);
		var->ray[TH]->var = var;
		var->ray[TH]->th = TH;
		var->ray[TH]->lol = 0;
	}
}

void	init_raytracing(t_ray *ray)
{
	CAM_DIR = unit_vector(fill_vector(-ray->CAM_POS.x, -ray->CAM_POS.y,
				-ray->CAM_POS.z));
	if (!ray->lol)
		CAM_UP = fill_vector(0, 1, 0);
	else
		CAM_UP = unit_vector(perp_vectors(CAM_DIR, CAM_RIGHT));
	CAM_RIGHT = unit_vector(perp_vectors(CAM_DIR, CAM_UP));
	VIEW_PLANE_DIST = ray->CAM_POS.z / 100;
	VIEW_PLANE_WIDTH = ray->WIDTH_WIN / 1000;
	VIEW_PLANE_HEIGHT = ray->HEIGHT_WIN / 1000;
	VIEW_PLANE_UPLEFT = add_vectors(ray->CAM_POS, sub_vectors(
				add_vectors(time_vector(CAM_DIR, VIEW_PLANE_DIST),
					time_vector(CAM_UP, VIEW_PLANE_HEIGHT / 2.0)),
			time_vector(CAM_RIGHT, VIEW_PLANE_WIDTH / 2.0)));
	X_INDENT = VIEW_PLANE_WIDTH / (double)ray->var->width_win;
	Y_INDENT = VIEW_PLANE_HEIGHT / (double)ray->var->height_win;
	ray->lol = 1;
}

void	rtv1(fd)
{
	t_var *var;

	if (!(var = (t_var *)ft_memalloc(sizeof(t_var))))
		exit(EXIT_FAILURE);
	parse_doc(fd, var);
	init_variables(var);
	mlx_loop_hook(MLX, launch_rtv1, var);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key, var);
	mlx_hook(WIN, DestroyNotify, Button1MotionMask, ft_crossquit, var);
	mlx_loop(MLX);
}

int		main(int ac, char **av)
{
	int		fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd > 0)
			rtv1(fd);
		close(fd);
	}
	return (0);
}
