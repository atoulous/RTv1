/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_rtv1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:43:30 by atoulous          #+#    #+#             */
/*   Updated: 2016/09/30 15:47:34 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_raytracing(int th, t_var *var)
{
	var->ray[th]->pos_x = 0;
	var->ray[th]->pos_y = 0;
	var->ray[th]->pos_z = 0;
}

void	*raytracing(void *arg)
{
	t_var		*var;
	int			x;

	var = (t_var *)arg;
	init_raytracing(TH, var);
	x = TH * (WIDTH_WIN / NB_TH) - 1;
	while (++x <= (TH + 1) * (WIDTH_WIN / NB_TH))
	{
		//do_raytracing;
		fill_image(var, x, 200, 0xFFFFFF);
	}
	pthread_exit(0);
}

int		launch_rtv1(t_var *var)
{
	pthread_t	th[NB_TH];

	TH = -1;
	while (++TH < NB_TH)
		if (pthread_create(&th[TH], NULL, &raytracing, var))
			exit(EXIT_FAILURE);
	TH = -1;
	while (++TH < NB_TH)
		pthread_join(th[TH], NULL);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}
