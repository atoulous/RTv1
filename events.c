/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:50:37 by atoulous          #+#    #+#             */
/*   Updated: 2016/11/30 19:24:28 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		restart_rt(t_var *var)
{
	(void)var;
	return (0);
}

int		ft_reset_screen(t_var *var)
{
	int		x;
	int		y;

	y = -1;
	while (++y < HEIGHT_WIN)
	{
		x = -1;
		while (++x < WIDTH_WIN)
		{
			var->ray[0]->x = x;
			var->ray[0]->y = y;
			fill_image(var->ray[0], 0, 1);
		}
	}
	return (0);
}

int		ft_key(int keycode, t_var *var)
{
	//ft_reset_screen(var);
	keycode == 53 ? ft_crossquit(var) : 0;
	keycode == 51 ? restart_rt(var) : 0;
	keycode == 123 ? CAM_POS.x += 10 : 0;
	keycode == 124 ? CAM_POS.x -= 10 : 0;
	keycode == 125 ? CAM_POS.y += 10 : 0;
	keycode == 126 ? CAM_POS.y -= 10 : 0;
	keycode == 27 ? CAM_POS.z -= 10 : 0;
	keycode == 24 ? CAM_POS.z += 10 : 0;
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
