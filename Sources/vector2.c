/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <atoulous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 19:22:27 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/09 19:47:57 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/rtv1.h"

double		angle_vectors(t_vector v1, t_vector v2)
{
	double ret;

	ret = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (ret);
}

t_vector	perp_vectors(t_vector v1, t_vector v2)
{
	t_vector ret;

	ret.x = (v1.y * v2.z - v2.y * v1.z);
	ret.y = (v1.x * v2.z - v2.x * v1.z);
	ret.z = (v1.x * v2.y - v2.x * v1.y);
	return (ret);
}

t_vector	time_vector(t_vector v, double i)
{
	t_vector ret;

	ret.x = v.x * i;
	ret.y = v.y * i;
	ret.z = v.z * i;
	return (ret);
}

t_vector	add_vectors(t_vector v1, t_vector v2)
{
	t_vector ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_vector	sub_vectors(t_vector v1, t_vector v2)
{
	t_vector ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}
