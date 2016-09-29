/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_rtv1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:43:30 by atoulous          #+#    #+#             */
/*   Updated: 2016/09/29 15:56:31 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	raytracing(int x, t_var *var)
{
}

int		launch_rtv1(t_var *var)
{
	int		x;

	x = -1;
	while (++x < WIDTH_WIN)
		raytracing(x, var);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}
