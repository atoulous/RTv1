/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <atoulous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 19:24:07 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/09 19:13:30 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	check_object_size(t_var *var)
{
	char	*size;

	if (!(size = parse_str(OBJ_STR, "size ", 0, var)))
		ft_exit("pas d'object size");
	else
	{
		OBJ_SIZE = ft_atof(size);
		free(size);
	}
}

void	check_object_origin(t_var *var)
{
	char	*tmp;
	char	**tab;

	if (!ft_strcmp(OBJ_TYPE, "sphere"))
		check_object_size(var);
	if (!(tmp = parse_str(OBJ_STR, "origin ", 0, var)))
		OBJ_ORIGIN = fill_vector(0, 0, 0);
	else
	{
		tab = ft_strsplit(tmp, ' ');
		if (!tab[0] || !tab[1] || !tab[2])
			ft_exit("problem object origin");
		OBJ_ORIGIN = fill_vector(ft_atof(tab[0]), ft_atof(tab[1]),
				ft_atof(tab[2]));
		ft_free2tab(tab);
		free(tmp);
	}
}

void	check_object_normale(t_var *var)
{
	char	*tmp;
	char	**tab;

	if (!(tmp = parse_str(OBJ_STR, "normale ", 0, var)))
		ft_exit("pas de normale");
	else
	{
		tab = ft_strsplit(tmp, ' ');
		if (!tab[0] || !tab[1] || !tab[2])
			ft_exit("problem object normale");
		OBJ_NORMALE = fill_vector(ft_atof(tab[0]), ft_atof(tab[1]),
				ft_atof(tab[2]));
		ft_free2tab(tab);
		free(tmp);
	}
}

void	check_object_color(t_var *var)
{
	char	*color;

	if ((OBJ_RGB = parse_str(OBJ_STR_COLOR, "rgb ", 0, var)))
	{
		color = ft_convert_base(OBJ_RGB, BASE16, BASE10);
		OBJ_COLOR = ft_atoi(color);
		free(color);
	}
	else
		OBJ_COLOR = 0xFF0000;
}

void	check_object_param(t_var *var)
{
	if (!(var->object[OBJ] = (t_obj *)ft_memalloc(sizeof(t_obj))))
		exit(EXIT_FAILURE);
	OBJ_STR = parse_str(DOC + COUNT, "object ", 1, var);
	if (!(OBJ_NAME = parse_str(OBJ_STR, "name ", 0, var)))
		ft_exit("pas d'object name");
	if (!(OBJ_TYPE = parse_str(OBJ_STR, "type ", 0, var)))
		ft_exit("pas d'object type");
	if (ft_strcmp(OBJ_TYPE, "cylinder") && ft_strcmp(OBJ_TYPE, "cone"))
		check_object_origin(var);
	else
	{
		check_object_size(var);
		check_cylinder_cone_origins(var);
	}
	if (!ft_strcmp(OBJ_TYPE, "plane"))
		check_object_normale(var);
	if (!(OBJ_STR_COLOR = parse_str(OBJ_STR, "color ", 0, var)))
		ft_exit("pas d'object color");
	else
		check_object_color(var);
}
