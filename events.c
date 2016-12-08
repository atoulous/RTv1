/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 14:50:37 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/08 19:50:07 by atoulous         ###   ########.fr       */
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
	return (0);
}
