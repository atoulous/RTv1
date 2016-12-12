/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/25 18:46:32 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/12 18:22:05 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/rtv1.h"

double		norm_vector(t_vector v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	unit_vector(t_vector v)
{
	t_vector	ret;
	double		norm;

	norm = norm_vector(v);
	ret.x = v.x / norm;
	ret.y = v.y / norm;
	ret.z = v.z / norm;
	return (ret);
}

t_vector	fill_vector(double x, double y, double z)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vector	*new_vector(double x, double y, double z)
{
	t_vector	*v;

	if ((v = malloc(sizeof(t_vector))) == NULL)
		exit(EXIT_FAILURE);
	v->x = x;
	v->y = y;
	v->z = z;
	return (v);
}
