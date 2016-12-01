/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_rtv1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:43:30 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/01 18:25:54 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	calc_sphere(t_ray *ray, t_vector ray_dir, t_vector ray_source, int i)
{
	double		t1;
	double		t2;
	double		t;

	A = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	B = 2.0 * (ray_dir.x * (ray_source.x - ROBJ_ORIGIN.x)
			+ ray_dir.y * (ray_source.y - ROBJ_ORIGIN.y)
			+ ray_dir.z * (ray_source.z - ROBJ_ORIGIN.z));
	C = (pow(ray_source.x - ROBJ_ORIGIN.x, 2.0)
			+ pow(ray_source.y - ROBJ_ORIGIN.y, 2.0)
			+ pow(ray_source.z - ROBJ_ORIGIN.z, 2.0))
		- pow(ray->var->object[i]->obj_size, 2.0);
	DET = B * B - 4.0 * A * C;
	t = 0;
	if (DET > 0.0)
	{
		t1 = (-B + sqrt(DET)) / (2.0 * A);
		t2 = (-B - sqrt(DET)) / (2.0 * A);
		t1 > t2 ? t = t2 : (t = t1);
	}
	else if (DET == 0.0)
		t = -B / (2.0 * A);
	return (t);
}

double	calc_plane(t_ray *ray, t_vector ray_dir, t_vector ray_source, int i)
{
	double		x;
	double		y;
	double		z;
	double		d;
	double		div;
	double		t;

	x = ray_source.x - ROBJ_ORIGIN.x;
	y = ray_source.y - ROBJ_ORIGIN.y;
	z = ray_source.z - ROBJ_ORIGIN.z;
	d = - angle_vectors(ROBJ_NORMALE, ROBJ_ORIGIN);
	div = angle_vectors(ROBJ_NORMALE, ray_dir);
	t = 0;
	if (div != 0.000000)
		t = - (((ROBJ_NORMALE.x * x + ROBJ_NORMALE.y * y + ROBJ_NORMALE.z * z)
		+ d) / div);
	return (t);
}

double	calc_shadows(t_ray *ray, t_vector ray_spot, t_vector pos_inter, int i, int j)
{
	double	t;

	t = 0;
	if (!ft_strcmp(ROBJ_TYPE, "sphere"))
		t = calc_sphere(ray, ray_spot, pos_inter, i);
	else if (!ft_strcmp(ROBJ_TYPE, "plane"))
		t = calc_plane(ray, ray_spot, pos_inter, i);
	//if (t > 0.000001)
	//	printf("%f\n", t);
	return (t == T_MAX - T? 1 : 0);
}

double		calc_angle(t_ray *ray, t_vector ray_dir, int i, int j)
{
	t_vector	normale_obj;
	t_vector	ray_spot;
	t_vector	ray_spot2;
	t_vector	pos_inter;
	double angle;

	pos_inter = add_vectors(ray->CAM_POS, time_vector(ray_dir, T));
	ray_spot = unit_vector(sub_vectors(pos_inter, RSPOT_ORIGIN));
	ray_spot2 = unit_vector(sub_vectors(RSPOT_ORIGIN, pos_inter));//retour
	if (calc_shadows(ray, ray_spot, RSPOT_ORIGIN, i, j)) // si il y a pos_intersection avant 
		return (0);
	normale_obj = unit_vector(sub_vectors(ROBJ_ORIGIN, pos_inter));
	angle = angle_vectors(ray_spot, normale_obj);
	return (angle);
}

void	multi_spot(t_ray *ray, t_vector ray_dir, int i)
{
	int		j;

	j = -1;
	while (++j < ray->var->nb_spot)
	{
		ANGLE = calc_angle(ray, ray_dir, i, j);
		ANGLE > ANGLE_MIN ? ANGLE_MIN = ANGLE : 0;
	}
	ray->var->nb_spot == 0 ? ANGLE_MIN = 1 : 0; //FOR NO SPOT
	if (ANGLE_MIN > 0.000000)
		fill_image(ray, ROBJ_COLOR, ANGLE_MIN);
	else
		fill_image(ray, 0, 1);
	T_MIN = T;
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
		ANGLE = 1;
		ANGLE_MIN = -1;
		if (!ft_strcmp(ROBJ_TYPE, "sphere"))
			T = calc_sphere(ray, RAY_DIR, ray->CAM_POS, i);
		else if (!ft_strcmp(ROBJ_TYPE, "plane"))
			T = calc_plane(ray, RAY_DIR, ray->CAM_POS, i);
		T > T_MAX ? T_MAX = T : 0;
		if (T > 0.000001 && T < T_MIN)
			multi_spot(ray, RAY_DIR, i);
	}
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
