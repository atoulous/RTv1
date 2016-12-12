/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 15:00:18 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/12 17:07:39 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/rtv1.h"

void	free_spot(t_var *var)
{
	SPOT_STR ? free(SPOT_STR) : 0;
	SPOT_NAME ? free(SPOT_NAME) : 0;
	SPOT_TYPE ? free(SPOT_TYPE) : 0;
	SPOT_STR_COLOR ? free(SPOT_STR_COLOR) : 0;
	SPOT_RGB ? free(SPOT_RGB) : 0;
}

void	free_obj(t_var *var)
{
	OBJ_STR ? free(OBJ_STR) : 0;
	OBJ_NAME ? free(OBJ_NAME) : 0;
	OBJ_TYPE ? free(OBJ_TYPE) : 0;
	OBJ_STR_COLOR ? free(OBJ_STR_COLOR) : 0;
	OBJ_RGB ? free(OBJ_RGB) : 0;
	var->object[OBJ] ? free(var->object[OBJ]) : 0;
}

void	free_all(t_var *var)
{
	IMG ? mlx_destroy_image(MLX, IMG) : 0;
	MLX = NULL;
	WIN = NULL;
	IMG = NULL;
	TH = -1;
	while (++TH < NB_TH)
		var->ray[TH] ? free(var->ray[TH]) : 0;
	OBJ = -1;
	while (++OBJ < NB_OBJ)
		free_obj(var);
	var->object ? free(var->object) : 0;
	SPO = -1;
	while (++SPO < NB_SPOT)
		free_spot(var);
	var->spot ? free(var->spot) : 0;
	DOC ? free(DOC) : 0;
	SCENE_NAME ? free(SCENE_NAME) : 0;
	CAMERA ? free(CAMERA) : 0;
	ORIGIN ? free(ORIGIN) : 0;
	RENDER ? free(RENDER) : 0;
	var ? free(var) : 0;
}

void	exit_free(t_var *var, char *str)
{
	free_all(var);
	ft_exit(str);
}

int		ft_crossquit(t_var *var)
{
	free_all(var);
	ft_exit("rtv1 quit, all well freed");
	return (0);
}
