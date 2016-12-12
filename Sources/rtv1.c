/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:06:17 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/12 17:29:54 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/rtv1.h"

void	fill_image(t_ray *ray, int color, double angle)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (angle >= 0.100 && angle < 1)
	{
		r = (color & 0xFF) * angle;
		g = ((color & 0xFF00) >> 8) * angle;
		b = ((color & 0xFF0000) >> 16) * angle;
	}
	else
	{
		r = (color & 0xFF) * 0.100;
		g = ((color & 0xFF00) >> 8) * 0.100;
		b = ((color & 0xFF0000) >> 16) * 0.100;
	}
	if (angle >= 0.990000 && angle < 1 && ray->BRILLANCE)
	{
		r += (255 - r) * (angle - 0.99) / 0.01;
		g += (255 - g) * (angle - 0.99) / 0.01;
		b += (255 - b) * (angle - 0.99) / 0.01;
	}
	ray->DATA[Y * ray->SIZELINE + X * (ray->BPP / 8)] = r;
	ray->DATA[Y * ray->SIZELINE + X * (ray->BPP / 8) + 1] = g;
	ray->DATA[Y * ray->SIZELINE + X * (ray->BPP / 8) + 2] = b;
}

int		launch_rtv1(t_var *var)
{
	pthread_t	th[NB_TH];

	TH = -1;
	while (++TH < NB_TH)
		if (pthread_create(&th[TH], NULL, &perform_rtv1, var->ray[TH]))
			exit(EXIT_FAILURE);
	TH = -1;
	while (++TH < NB_TH)
		pthread_join(th[TH], NULL);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}

void	rtv1(int fd)
{
	t_var	*var;

	if (!(var = (t_var *)ft_memalloc(sizeof(t_var))))
		ft_exit("Var Malloc Error");
	parse_doc(fd, var);
	init_variables(var);
	launch_rtv1(var);
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
	else
		ft_putendl("Choose demo");
	return (0);
}
