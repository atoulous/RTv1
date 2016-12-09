/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:50:37 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/09 16:53:45 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_key(int keycode, t_var *var)
{
	keycode == 53 ? ft_crossquit(var) : 0;
	keycode == 123 ? CAM_POS.x -= 5 : 0;
	keycode == 124 ? CAM_POS.x += 5 : 0;
	keycode == 125 ? CAM_POS.y += 10 : 0;
	keycode == 126 ? CAM_POS.y -= 10 : 0;
	keycode == 27 ? CAM_POS.z -= 10 : 0;
	keycode == 24 ? CAM_POS.z += 10 : 0;
	keycode == 75 ? var->luminosite -= 0.1 : 0;
	keycode == 67 ? var->luminosite += 0.1 : 0;
	return (0);
}
