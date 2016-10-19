/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:50:37 by atoulous          #+#    #+#             */
/*   Updated: 2016/10/17 19:34:19 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_key(int keycode, t_var *var)
{
	keycode == 53 ? ft_crossquit(var) : 0;
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

int		ft_crossquit(t_var *var)
{
	free_all(var);
	exit(EXIT_SUCCESS);
}
