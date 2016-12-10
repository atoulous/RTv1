/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_rtv1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:43:30 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/10 20:14:49 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/rtv1.h"

double	calc_shadows(t_ray *ray, t_vector ray_dir, int j)
{
	t_vector	ray_spot;
	t_vector	pos_spot;
	double		t;
	int			i;

	pos_spot = add_vectors(ray->CAM_POS, time_vector(ray_dir, T_MIN));
	ray_spot = unit_vector(sub_vectors(RSPOT_ORIGIN, pos_spot));
	i = -1;
	while (++i < ray->var->nb_obj)
	{
		t = 0;
		if (!ft_strcmp(ROBJ_TYPE, "sphere") && i != T_OBJ)
			t = calc_sphere(ray, ray_spot, pos_spot, i);
		else if (!ft_strcmp(ROBJ_TYPE, "cylinder") && i != T_OBJ)
			t = calc_cylinder(ray, ray_spot, pos_spot, i);
		else if (!ft_strcmp(ROBJ_TYPE, "cone") && i != T_OBJ)
			t = calc_cone(ray, ray_spot, pos_spot, i);
		if (t > 0.000000)
			return (t);
	}
	return (0);
}

double	calc_angle(t_ray *ray, t_vector ray_dir, int i, int j)
{
	t_vector	normale_obj;
	t_vector	ray_spot;
	t_vector	pos_inter;
	double		l;

	pos_inter = add_vectors(ray->CAM_POS, time_vector(ray_dir, T_MIN));
	ray_spot = unit_vector(sub_vectors(pos_inter, RSPOT_ORIGIN));
	if (!ft_strcmp(ROBJ_TYPE, "sphere"))
		normale_obj = unit_vector(sub_vectors(ROBJ_ORIGIN, pos_inter));
	if (!ft_strcmp(ROBJ_TYPE, "plane"))
		normale_obj = unit_vector(sub_vectors(pos_inter, ROBJ_NORMALE));
	if (!ft_strcmp(ROBJ_TYPE, "cylinder") || !ft_strcmp(ROBJ_TYPE, "cone"))
	{
		l = norm_vector(sub_vectors(ROBJ_ORIGIN, pos_inter));
		if (!ft_strcmp(ROBJ_TYPE, "cylinder"))
			l = sqrt(l * l - ROBJ_SIZE * ROBJ_SIZE);
		else
			l = l / cos(ROBJ_SIZE * (M_PI / 180));
		normale_obj = unit_vector(sub_vectors(ROBJ_ORIGIN2, ROBJ_ORIGIN));
		if (angle_vectors(sub_vectors(ROBJ_ORIGIN, pos_inter), normale_obj) > 0)
			normale_obj = unit_vector(sub_vectors(ROBJ_ORIGIN, ROBJ_ORIGIN2));
		normale_obj = add_vectors(ROBJ_ORIGIN, time_vector(normale_obj, l));
		normale_obj = unit_vector(sub_vectors(normale_obj, pos_inter));
	}
	return (angle_vectors(ray_spot, normale_obj));
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
	ray->OMBRE == 1 ? ANGLE_MIN -= SHADOW : 0;
	((ANGLE_MIN + LUMINOSITE) < 1) && ((ANGLE_MIN - LUMINOSITE) > 0.0) ?
		ANGLE_MIN += LUMINOSITE : 0;
	ray->var->nb_spot == 0 ? ANGLE_MIN = 1 : 0;
	if (ANGLE_MIN)
		fill_image(ray, ROBJ_COLOR, ANGLE_MIN);
	else
		fill_image(ray, ROBJ_COLOR, 0);
}

void	raytracing(t_ray *ray)
{
	int			i;

	i = -1;
	while (++i < ray->var->nb_obj)
	{
		ray->i = i;
		if (!ft_strcmp(ROBJ_TYPE, "sphere"))
			T = calc_sphere(ray, RAY_DIR, ray->CAM_POS, i);
		else if (!ft_strcmp(ROBJ_TYPE, "plane"))
			T = calc_plane(ray, RAY_DIR, ray->CAM_POS, i);
		else if (!ft_strcmp(ROBJ_TYPE, "cylinder"))
			T = calc_cylinder(ray, RAY_DIR, ray->CAM_POS, i);
		else if (!ft_strcmp(ROBJ_TYPE, "cone"))
			T = calc_cone(ray, RAY_DIR, ray->CAM_POS, i);
		if (T > 0.000001 && T < T_MIN)
		{
			T_OBJ = i;
			T_MIN = T;
		}
	}
	if (T_OBJ != -1)
		multi_spot(ray, RAY_DIR, T_OBJ);
	else
		fill_image(ray, 0, 0);
}

void	*perform_rtv1(void *arg)
{
	t_ray		*ray;
	t_var		*var;

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
			T_OBJ = -1;
			RAY_DIR = unit_vector(sub_vectors(ray->CAM_POS, add_vectors(
				VIEW_PLANE_UPLEFT, sub_vectors(time_vector(CAM_RIGHT,
				X_INDENT * X), time_vector(CAM_UP, Y_INDENT * Y)))));
			raytracing(ray);
		}
	}
	pthread_exit(0);
}
