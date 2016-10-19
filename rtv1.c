/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:06:17 by atoulous          #+#    #+#             */
/*   Updated: 2016/10/19 13:20:19 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	fill_image(t_var *var, int x, int y, int color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = color >> 0;
	g = color >> 8;
	b = color >> 16;
	if (x >= 0 && x < WIDTH_WIN && y >= 0 && y < HEIGHT_WIN)
	{
		DATA[y * SIZELINE + x * (BPP / 8)] = r;
		DATA[y * SIZELINE + x * (BPP / 8) + 1] = g;
		DATA[y * SIZELINE + x * (BPP / 8) + 2] = b;
	}
}

void	init_environnement(t_var *var)
{
	WIDTH_WIN = 1080;
	HEIGHT_WIN = 800;
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, WIDTH_WIN, HEIGHT_WIN, "RTV1");
	IMG = mlx_new_image(MLX, WIDTH_WIN, HEIGHT_WIN);
	DATA = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	var->th = -1;
	while (++TH < NB_TH)
		if (!(var->ray[TH] = (t_ray *)ft_memalloc(sizeof(t_ray))))
			exit(EXIT_FAILURE);
}

void	rtv1(fd)
{
	t_var *var;

	if (!(var = (t_var *)ft_memalloc(sizeof(t_var))))
		exit(EXIT_FAILURE);
	init_environnement(var);
	parse_doc(fd, var);
	mlx_loop_hook(MLX, launch_rtv1, var);
	mlx_hook(WIN, KeyPress, KeyPressMask, ft_key, var);
	mlx_hook(WIN, KeyRelease, KeyReleaseMask, ft_release, var);
	mlx_hook(WIN, ButtonPress, ButtonPressMask, ft_mouse, var);
	mlx_hook(WIN, MotionNotify, ButtonMotionMask, ft_motion_mouse, var);
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
