/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rtv1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <atoulous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:39:09 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/12 17:51:52 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/rtv1.h"

void	init_variables(t_var *var)
{
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, WIDTH_WIN, HEIGHT_WIN, SCENE_NAME);
	IMG = mlx_new_image(MLX, WIDTH_WIN, HEIGHT_WIN);
	DATA = mlx_get_data_addr(IMG, &BPP, &SIZELINE, &ENDIAN);
	var->luminosite = 0.0;
	TH = -1;
	while (++TH < NB_TH)
	{
		if (!(var->ray[TH] = (t_ray *)ft_memalloc(sizeof(t_ray))))
			exit(EXIT_FAILURE);
		var->ray[TH]->var = var;
		var->ray[TH]->th = TH;
	}
}

void	init_raytracing(t_ray *ray)
{
	CAM_DIR = unit_vector(fill_vector(-ray->CAM_POS.x, -ray->CAM_POS.y,
				-ray->CAM_POS.z));
	CAM_UP = fill_vector(0, -1, 0);
	CAM_RIGHT = unit_vector(perp_vectors(CAM_UP, CAM_DIR));
	CAM_UP = unit_vector(perp_vectors(CAM_DIR, CAM_RIGHT));
	VIEW_PLANE_DIST = -1;
	VIEW_PLANE_WIDTH = ray->WIDTH_WIN / 1000;
	VIEW_PLANE_HEIGHT = ray->HEIGHT_WIN / 1000;
	VIEW_PLANE_UPLEFT = add_vectors(ray->CAM_POS, sub_vectors(
				add_vectors(time_vector(CAM_DIR, VIEW_PLANE_DIST),
					time_vector(CAM_UP, VIEW_PLANE_HEIGHT / 2.0)),
			time_vector(CAM_RIGHT, VIEW_PLANE_WIDTH / 2.0)));
	X_INDENT = VIEW_PLANE_WIDTH / (double)ray->var->width_win;
	Y_INDENT = VIEW_PLANE_HEIGHT / (double)ray->var->height_win;
}
