/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_rtv1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:43:30 by atoulous          #+#    #+#             */
/*   Updated: 2016/11/21 20:02:39 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	calc_sphere(t_ray *ray, t_vector ray_dir, int i)
{
	double		a;
	double		b;
	double		c;
	double		det;
	double		t1;
	double		t2;
	double		t;

	a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	b = 2.0 * (ray_dir.x * (ray->CAM_POS.x - ray->var->object[i]->obj_origin.x)
			+ ray_dir.y * (ray->CAM_POS.y - ray->var->object[i]->obj_origin.y)
			+ ray_dir.z * (ray->CAM_POS.z - ray->var->object[i]->obj_origin.z));
	c = (pow(ray->CAM_POS.x - ray->var->object[i]->obj_origin.x, 2.0)
			+ pow(ray->CAM_POS.y - ray->var->object[i]->obj_origin.y, 2.0)
			+ pow(ray->CAM_POS.z - ray->var->object[i]->obj_origin.z, 2.0))
		- pow(ray->var->object[i]->obj_size, 2.0);
	det = b * b - 4.0 * a * c;
	if (det > 0.0)
	{
		t1 = (-b + sqrt(det)) / (2.0 * a);
		t2 = (-b - sqrt(det)) / (2.0 * a);
		t1 < t2 ? (t = t1) : (t = t2);
		RAY = unit_vector(add_vectors(ray->CAM_POS, time_vector(ray_dir, t)));
		HIT = 1;
	}
	else if (det == 0.0)
	{
		t = -b / (2.0 * a);
		RAY = unit_vector(add_vectors(ray->CAM_POS, time_vector(ray_dir, t)));
		HIT = 1;
	}
	else
		HIT = 0;
}

void	raytracing(t_ray *ray, int x, int y)
{
	t_vector	ray_dir;
	int			obj;

	ray_dir = unit_vector(sub_vectors(add_vectors(VIEW_PLANE_UPLEFT,
					time_vector(CAM_RIGHT, X_INDENT * x)),
				time_vector(CAM_UP, Y_INDENT * y)));
	obj = -1;
	while (++obj < ray->var->nb_obj)
	{
		HIT = 0;
		if (!ft_strcmp(ray->var->object[obj]->type, "sphere"))
			calc_sphere(ray, ray_dir, obj);
		if (HIT == 1)
			fill_image(ray->var, x, y, ray->var->object[obj]->obj_color);
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
	x = TH * (WIDTH_WIN / NB_TH) - 1;
	while (++x < (TH + 1) * (WIDTH_WIN / NB_TH))
	{
		y = -1;
		while (++y < HEIGHT_WIN)
			raytracing(ray, x, y);
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
