/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:50:37 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/12 15:41:09 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/rtv1.h"

int		ft_key(int keycode, t_var *var)
{
	keycode == 53 ? ft_crossquit(var) : 0;
	keycode == 123 ? CAM_POS.x -= 5 : 0;
	keycode == 124 ? CAM_POS.x += 5 : 0;
	keycode == 125 ? CAM_POS.y += 5 : 0;
	keycode == 126 ? CAM_POS.y -= 5 : 0;
	keycode == 27 ? CAM_POS.z -= 5 : 0;
	keycode == 24 ? CAM_POS.z += 5 : 0;
	keycode == 75 ? var->luminosite -= 0.1 : 0;
	keycode == 67 ? var->luminosite += 0.1 : 0;
	if (keycode == 11)
	{
		if (BRILLANCE == 1)
			BRILLANCE = 0;
		else
			BRILLANCE = 1;
	}
	if (keycode == 31)
	{
		if (OMBRE == 1)
			OMBRE = 0;
		else
			OMBRE = 1;
	}
	return (0);
}
