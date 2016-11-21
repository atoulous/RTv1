/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:50:37 by atoulous          #+#    #+#             */
/*   Updated: 2016/11/21 18:50:22 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*int		restart_rt(t_var *var)
{
	char	*doc;
	t_var	*var2;

	doc = ft_strdup(DOC);
	free_all(var);
	if (!(var2 = (t_var *)ft_memalloc(sizeof(t_var))))
		exit(EXIT_FAILURE);
	var = var2;
	DOC = doc;
	NB_OBJ = ft_nbstrstr(DOC, "object ");
	if (!(var->object = (t_obj **)ft_memalloc(sizeof(t_obj *) * NB_OBJ)))
		exit(EXIT_FAILURE);
	I = 0;
	check_scene_param(var, NULL, NULL);
	check_object_param(var);
	init_variables(var);
	return (0);
}*/

int		ft_reset_screen(t_var *var)
{
	int		x;
	int		y;

	y = -1;
	while (++y < HEIGHT_WIN)
	{
		x = -1;
		while (++x < WIDTH_WIN)
			fill_image(var, x, y, 0);
	}
	return (0);
}

int		ft_key(int keycode, t_var *var)
{
	ft_reset_screen(var);
	keycode == 53 ? ft_crossquit(var) : 0;
	//keycode == 51 ? restart_rt(var) : 0;
	keycode == 123 ? CAM_POS.x += 10 : 0;
	keycode == 124 ? CAM_POS.x -= 10 : 0;
	keycode == 125 ? CAM_POS.y += 10 : 0;
	keycode == 126 ? CAM_POS.y -= 10 : 0;
	return (0);
}

int		ft_press(int keycode, t_var *var)
{
	keycode = 0;
	(void)var;
	return (0);
}

int		ft_release(int keycode, t_var *var)
{
	keycode = 0;
	(void)var;
	return (0);
}

int		ft_mouse(int button, int x, int y, t_var *var)
{
	button = 0;
	x = 0;
	y = 0;
	(void)var;
	return (0);
}

int		ft_motion_mouse(int x, int y, t_var *var)
{
	x = 0;
	y = 0;
	(void)var;
	return (0);
}
