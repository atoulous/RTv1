/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 16:56:41 by atoulous          #+#    #+#             */
/*   Updated: 2016/11/30 13:46:42 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*parse_str(char *doc, char *str, int mode, t_var *var)
{
	char	*res;
	int		o;
	int		i;

	res = NULL;
	if (doc && str && (res = ft_strstr(doc, str)))
	{
		o = 0;
		i = -1;
		while (res[++i])
		{
			if (res[i] == '{')
				o++;
			if (res[i] == '}' && o == 1)
				break ;
			if (res[i] == '}')
				o--;
		}
		res = ft_strndup(res + ft_strlen(str) + 2, i - (ft_strlen(str) + 2));
		res = ft_strtrimfree(res);
		mode == 1 ? COUNT += i : 0;
	}
	mode == 2 && doc ? free(doc) : 0;
	return (res);
}

void	check_spot_origin(t_var *var)
{
	char	*tmp;
	char	**tab;

	if (!(tmp = parse_str(SPOT_STR, "origin ", 0, var)))
		SPOT_ORIGIN = fill_vector(0, 0, 0);
	else
	{
		tab = ft_strsplit(tmp, ' ');
		if (!tab[0] || !tab[1] || !tab[2])
			ft_exit("problem spot origin");
		SPOT_ORIGIN = fill_vector(ft_atof(tab[0]), ft_atof(tab[1]),
				ft_atof(tab[2]));
		ft_free2tab(tab);
		free(tmp);
	}
}

void	check_spot_param(t_var *var)
{
	char	*color;

	SPO = -1;
	while (++SPO < NB_SPOT)
	{
		if (!(var->spot[SPO] = (t_spot *)ft_memalloc(sizeof(t_spot))))
			exit(EXIT_FAILURE);
		SPOT_STR = parse_str(DOC + COUNT, "spot ", 1, var);
		if (!(SPOT_NAME = parse_str(SPOT_STR, "name ", 0, var)))
			ft_exit("pas de spot name");
		check_spot_origin(var);
		if (!(SPOT_STR_COLOR = parse_str(SPOT_STR, "color ", 0, var)))
			ft_exit("pas de spot color");
		else
		{
			if (!(SPOT_RGB = parse_str(SPOT_STR_COLOR, "rgb ", 0, var)))
				SPOT_COLOR = 0xFFFFFF;
			if ((color = ft_convert_base(SPOT_RGB, BASE16, BASE10)))
			{
				SPOT_COLOR = ft_atoi(color);
				free(color);
			}
		}
	}
}

void	check_object_size(t_var *var)
{
	char	*size;
	char	**tab;

	if (!(size = parse_str(OBJ_STR, "size ", 0, var)))
		ft_exit("pas d'object size");
	else
	{
		if (!ft_strcmp(OBJ_TYPE, "sphere"))
			OBJ_SIZE = ft_atof(size);
		else if (!ft_strcmp(OBJ_TYPE, "plane"))
		{
			if (!(tab = ft_strsplit(size, ' ')) || !tab[0] || !tab[1])
				ft_exit("pas de plane width or height");
			else
			{
				OBJ_SIZE_WIDTH = ft_atof(tab[0]);
				OBJ_SIZE_HEIGHT = ft_atof(tab[1]);
				ft_free2tab(tab);
			}
		}
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

void	check_object_param(t_var *var)
{
	char	*color;

	OBJ = -1;
	while (++OBJ < NB_OBJ)
	{
		if (!(var->object[OBJ] = (t_obj *)ft_memalloc(sizeof(t_obj))))
			exit(EXIT_FAILURE);
		OBJ_STR = parse_str(DOC + COUNT, "object ", 1, var);
		if (!(OBJ_NAME = parse_str(OBJ_STR, "name ", 0, var)))
			ft_exit("pas d'object name");
		if (!(OBJ_TYPE = parse_str(OBJ_STR, "type ", 0, var)))
			ft_exit("pas d'object type");
		check_object_origin(var);
		if (!ft_strcmp(OBJ_TYPE, "plane"))
			check_object_normale(var);
		if (!(OBJ_STR_COLOR = parse_str(OBJ_STR, "color ", 0, var)))
			ft_exit("pas d'object color");
		else
		{
			if ((OBJ_RGB = parse_str(OBJ_STR_COLOR, "rgb ", 0, var)))
			{
				color = ft_convert_base(OBJ_RGB, BASE16, BASE10);
				OBJ_COLOR = ft_atoi(color);
				free(color);
			}
			else
				OBJ_COLOR = 0xFF0000;
		}
	}
}

void	check_scene_param(t_var *var, char **tb, char *size)
{
	if (!(SCENE_NAME = parse_str(DOC, "name ", 1, var)))
		ft_exit("pas de scene_name");
	if (!(CAMERA = parse_str(DOC, "camera ", 1, var)))
		ft_exit("pas de param camera");
	else
	{
		if (!(ORIGIN = parse_str(CAMERA, "origin ", 0, var)))
			CAM_POS = fill_vector(-1.0, -1.0, -1.0);
		else
		{
			tb = ft_strsplit(ORIGIN, ' ');
			CAM_POS = fill_vector(ft_atof(tb[0]), ft_atof(tb[1]), ft_atof(tb[2]));
			ft_free2tab(tb);
		}
	}
	if (!(RENDER = parse_str(DOC, "render ", 1, var)))
		ft_exit("pas de param render");
	if (!(size = parse_str(RENDER, "mlx_all_objects ", 0, var)))
		size = ft_strdup("9080 800");
	tb = ft_strsplit(size, ' ');
	WIDTH_WIN = ft_atof(tb[0]);
	HEIGHT_WIN = ft_atof(tb[1]);
	ft_free2tab(tb);
	free(size);
}

void	parse_doc(int fd, t_var *var)
{
	char	*line;

	COUNT = 0;
	DOC = ft_strnew(0);
	while (get_next_line(fd, &line))
	{
		DOC = ft_strjoinfree(DOC, line);
		DOC = ft_strjoinfree(DOC, "\n");
		free(line);
	}
	NB_OBJ = ft_nbstrstr(DOC, "object ");
	if (!(var->object = (t_obj **)ft_memalloc(sizeof(t_obj *) * NB_OBJ)))
		exit(EXIT_FAILURE);
	NB_SPOT = ft_nbstrstr(DOC, "spot ");
	if (!(var->spot = (t_spot **)ft_memalloc(sizeof(t_spot *) * NB_SPOT)))
		exit(EXIT_FAILURE);
	check_scene_param(var, NULL, NULL);
	check_object_param(var);
	check_spot_param(var);
	ft_putstr(DOC);
}
