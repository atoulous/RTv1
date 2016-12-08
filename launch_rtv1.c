/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_rtv1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:43:30 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/08 19:49:19 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		calc_angle(t_ray *ray, t_vector ray_dir, int i, int j)
{
	t_vector	normale_obj;
	t_vector	ray_spot;
	t_vector	pos_inter;
	double		angle;

	pos_inter = add_vectors(ray->CAM_POS, time_vector(ray_dir, T_MIN));
	ray_spot = unit_vector(sub_vectors(pos_inter, RSPOT_ORIGIN));
	normale_obj = unit_vector(sub_vectors(ROBJ_ORIGIN, pos_inter));
	angle = angle_vectors(ray_spot, normale_obj);
	return (angle);
}

void	multi_spot(t_ray *ray, t_vector ray_dir, int i)
{
	int		j;

	ANGLE = 0;
	ANGLE_MIN = 0;
	SHADOW = 0;
	j = -1;
	while (++j < ray->var->nb_spot)
	{
		ANGLE = calc_angle(ray, ray_dir, i, j);
		ANGLE > ANGLE_MIN ? ANGLE_MIN = ANGLE : 0;
		if (calc_shadows(ray, ray_dir, j))
			SHADOW += 0.4;
	}
	ray->var->nb_spot == 0 ? ANGLE_MIN = 1 : 0;
	ANGLE_MIN -= SHADOW;
	if (ANGLE_MIN > 0.000000)
		fill_image(ray, ROBJ_COLOR, ANGLE_MIN);
	else
		fill_image(ray, ROBJ_COLOR, 0);
}

void	raytracing(t_ray *ray)
{
	t_vector	pos_pix;
	int			i;

	pos_pix = add_vectors(VIEW_PLANE_UPLEFT, sub_vectors(
				time_vector(CAM_RIGHT, X_INDENT * X),
				time_vector(CAM_UP, Y_INDENT * Y)));
	RAY_DIR = unit_vector(sub_vectors(ray->CAM_POS, pos_pix));
	i = -1;
	while (++i < ray->var->nb_obj)
	{
		if (!ft_strcmp(ROBJ_TYPE, "sphere"))
			T = calc_sphere(ray, RAY_DIR, ray->CAM_POS, i);
		else if (!ft_strcmp(ROBJ_TYPE, "plane"))
			T = calc_plane(ray, RAY_DIR, ray->CAM_POS, i);
		else if (!ft_strcmp(ROBJ_TYPE, "cylinder"))
			T = calc_cylinder(ray, RAY_DIR, ray->CAM_POS, i);
		else if (!ft_strcmp(ROBJ_TYPE, "cone"))
			T = calc_cone(ray, RAY_DIR, ray->CAM_POS, i);
		T > T_MAX ? T_MAX = T : 0;
		if (T > 0.000001 && T < T_MIN)
		{
			T_OBJ = i;
			T_MIN = T;
		}
	}
	if (T_MIN != 1000000)
		multi_spot(ray, RAY_DIR, T_OBJ);
}

void	*multi_thread(void *arg)
{
	t_ray		*ray;
	t_var		*var;
	int			x;
	int			y;

	ray = (t_ray *)arg;
	var = ray->var;
	init_raytracing(ray);
	X = ray->th * (WIDTH_WIN / NB_TH) - 1;
	while (++X < (ray->th + 1) * (WIDTH_WIN / NB_TH))
	{
		Y = -1;
		while (++Y < HEIGHT_WIN)
		{
			T = 0;
			T_MIN = 1000000;
			T_MAX = 0;
			T_OBJ = 0;
			raytracing(ray);
		}
	}
	pthread_exit(0);
}

int		launch_rtv1(t_var *var)
{
	pthread_t	th[NB_TH];
	int			i;

	TH = -1;
	while (++TH < NB_TH)
		if (pthread_create(&th[TH], NULL, &multi_thread, var->ray[TH]))
			exit(EXIT_FAILURE);
	TH = -1;
	while (++TH < NB_TH)
		pthread_join(th[TH], NULL);
	mlx_put_image_to_window(MLX, WIN, IMG, 0, 0);
	return (0);
}
