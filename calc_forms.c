/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_forms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <atoulous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 19:15:39 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/09 19:00:54 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	calc_sphere(t_ray *ray, t_vector ray_dir, t_vector ray_source, int i)
{
	double		t1;
	double		t2;

	A = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	B = 2.0 * (ray_dir.x * (ray_source.x - ROBJ_ORIGIN.x)
			+ ray_dir.y * (ray_source.y - ROBJ_ORIGIN.y)
			+ ray_dir.z * (ray_source.z - ROBJ_ORIGIN.z));
	C = (pow(ray_source.x - ROBJ_ORIGIN.x, 2.0)
			+ pow(ray_source.y - ROBJ_ORIGIN.y, 2.0)
			+ pow(ray_source.z - ROBJ_ORIGIN.z, 2.0))
		- pow(ray->var->object[i]->obj_size, 2.0);
	DET = B * B - 4.0 * A * C;
	t1 = 0;
	if (DET > 0.0)
	{
		t1 = (-B + sqrt(DET)) / (2.0 * A);
		t2 = (-B - sqrt(DET)) / (2.0 * A);
		t1 > t2 ? t1 = t2 : 0;
	}
	else if (DET == 0.0)
		t1 = -B / (2.0 * A);
	return (t1 ? t1 : 0);
}

double	calc_plane(t_ray *ray, t_vector ray_dir, t_vector ray_source, int i)
{
	double		x;
	double		y;
	double		z;
	double		d;
	double		t;

	x = ray_source.x - ROBJ_ORIGIN.x;
	y = ray_source.y - ROBJ_ORIGIN.y;
	z = ray_source.z - ROBJ_ORIGIN.z;
	d = -angle_vectors(ROBJ_NORMALE, unit_vector(ROBJ_ORIGIN));
	t = angle_vectors(ROBJ_NORMALE, ray_dir);
	if (t != 0.000000)
		t = -(((ROBJ_NORMALE.x * x + ROBJ_NORMALE.y * y + ROBJ_NORMALE.z * z)
		+ d) / t);
	return (t > 0.000000 ? t : 0);
}

double	calc_cylinder(t_ray *ray, t_vector ray_dir, t_vector ray_source, int i)
{
	t_vector	normale_obj;
	t_vector	p;
	t_vector	tmp;
	double		t1;

	normale_obj = unit_vector(sub_vectors(ROBJ_ORIGIN2, ROBJ_ORIGIN));
	p = sub_vectors(ray_source, ROBJ_ORIGIN);
	tmp = sub_vectors(ray_dir, time_vector(normale_obj,
				angle_vectors(ray_dir, normale_obj)));
	A = angle_vectors(tmp, tmp);
	B = 2 * angle_vectors(sub_vectors(ray_dir, time_vector(normale_obj,
		angle_vectors(ray_dir, normale_obj))), sub_vectors(p,
		time_vector(normale_obj, angle_vectors(p, normale_obj))));
	tmp = sub_vectors(p, time_vector(normale_obj,
		angle_vectors(p, normale_obj)));
	C = angle_vectors(tmp, tmp) - ROBJ_SIZE * ROBJ_SIZE;
	DET = B * B - 4.0 * A * C;
	t1 = 0;
	if (DET > 0.0)
	{
		t1 = (-B + sqrt(DET)) / (2.0 * A);
		if (((-B - sqrt(DET)) / (2.0 * A)) < t1)
			t1 = (-B - sqrt(DET)) / (2.0 * A);
	}
	return (t1);
}

double	calc_cone_det(t_ray *ray, t_vector ray_dir, t_vector p, double alpha)
{
	t_vector	normale_obj;
	t_vector	tmp;
	int			i;

	i = ray->i;
	normale_obj = unit_vector(sub_vectors(ROBJ_ORIGIN2, ROBJ_ORIGIN));
	tmp = sub_vectors(ray_dir, time_vector(normale_obj,
				angle_vectors(ray_dir, normale_obj)));
	A = cos(alpha) * angle_vectors(tmp, tmp) - sin(alpha) *
		(angle_vectors(ray_dir, normale_obj)
		* angle_vectors(ray_dir, normale_obj));
	B = 2 * cos(alpha) * (angle_vectors(sub_vectors(ray_dir,
		time_vector(normale_obj, angle_vectors(ray_dir, normale_obj))),
		sub_vectors(p, time_vector(normale_obj,
		angle_vectors(p, normale_obj))))) - (2 * sin(alpha) *
		angle_vectors(ray_dir, normale_obj) * angle_vectors(p, normale_obj));
	tmp = sub_vectors(p, time_vector(normale_obj,
		angle_vectors(p, normale_obj)));
	C = cos(alpha) * angle_vectors(tmp, tmp) - sin(alpha)
		* (angle_vectors(p, normale_obj) * angle_vectors(p, normale_obj));
	return (B * B - 4.0 * A * C);
}

double	calc_cone(t_ray *ray, t_vector ray_dir, t_vector ray_source, int i)
{
	t_vector	p;
	double		alpha;
	double		t1;
	double		t2;

	alpha = ROBJ_SIZE * (M_PI / 180);
	p = sub_vectors(ray_source, ROBJ_ORIGIN);
	DET = calc_cone_det(ray, ray_dir, p, alpha);
	t1 = 0;
	if (DET > 0.0)
	{
		t1 = (-B + sqrt(DET)) / (2.0 * A);
		t2 = (-B - sqrt(DET)) / (2.0 * A);
		t1 > t2 ? t1 = t2 : 0;
	}
	else if (DET == 0.0)
		t1 = -B / (2.0 * A);
	return (t1);
}
