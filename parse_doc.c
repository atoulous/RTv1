/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 16:56:41 by atoulous          #+#    #+#             */
/*   Updated: 2016/10/19 20:03:43 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char	*parse_str(char *doc, char *str, int mode, t_var *var)
{
	char	*tmp;
	int		o;
	int		i;

	if ((tmp = ft_strstr(doc, str)))
	{
		o = 0;
		i = -1;
		while (tmp[++i])
		{
			if (tmp[i] == '{')
				o++;
			if (tmp[i] == '}' && o == 1)
				break;
			if (tmp[i] == '}')
				o--;
		}
		tmp = ft_strsub(tmp, ft_strlen(str) + 2, i - (ft_strlen(str) + 2));
		tmp = ft_strtrimfree(tmp);
		while (--i && mode == 1)
			CPY++;
	}
	else
		tmp = NULL;
	mode == 2 ? free(doc) : 0;
	return (tmp);
}

void	check_scene_param(t_var *var)
{
	if (!(SCENE_NAME = parse_str(DOC, "name", 1, var)))
		ft_putendl("pas de scene_name");
	if (!(CAMERA = parse_str(DOC, "camera", 1, var)))
		ft_putendl("pas de param camera");
	if (!(RENDER = parse_str(DOC, "render", 1, var)))
		ft_putendl("pas de param render");
}

void	convert_color(t_var *var)
{
	char	**tab;

	if (!(OBJ_STR_COLOR = parse_str(OBJ_STR_COLOR, "rgb ", 2, var)))
		ft_putendl("pas d'object color");
	ft_putendl(OBJ_STR_COLOR);
	tab = ft_strsplit(OBJ_STR_COLOR, ' ');
	while (tab)
		ft_putendl(*tab++);
}

void	check_object_param(t_var *var)
{
	NB_OBJ = ft_nbstrstr(DOC, "object ");
	OBJ = -1;
	if (!(var->object = (t_obj **)ft_memalloc(sizeof(t_obj *) * NB_OBJ)))
		exit(EXIT_FAILURE);
	while (++OBJ < NB_OBJ)
	{
		if (!(var->object[OBJ] = (t_obj *)ft_memalloc(sizeof(t_obj))))
			exit(EXIT_FAILURE);
		OBJ_STR = parse_str(CPY, "object ", 1, var);
		ft_putendl(OBJ_STR);
		if (!(OBJ_NAME = parse_str(OBJ_STR, "name ", 0, var)))
			ft_putendl("pas d'object name");
		ft_putendl(OBJ_NAME);
		if (!(OBJ_INTER = parse_str(OBJ_STR, "inter ", 0, var)))
			ft_putendl("pas d'object inter");
		ft_putendl(OBJ_INTER);
		if (!(OBJ_STR_COLOR = parse_str(OBJ_STR, "color ", 0, var)))
			ft_putendl("pas d'object color");
		ft_putendl(OBJ_STR_COLOR);
		convert_color(var);
	}
}

void	parse_doc(int fd, t_var *var)
{
	char	*line;
	int		i;

	DOC = ft_strnew(0);
	while (get_next_line(fd, &line))
	{
		DOC = ft_strjoinfree(DOC, line);
		DOC = ft_strjoinfree(DOC, "\n");
	}
	CPY = ft_strdup(DOC);
	ft_putstr(DOC);
	check_scene_param(var);
	ft_putendl("------------------");
	ft_putendl(SCENE_NAME);
	ft_putendl(CAMERA);
	ft_putendl(RENDER);
	check_object_param(var);
}
