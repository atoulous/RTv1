/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doc3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <atoulous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:11:08 by atoulous          #+#    #+#             */
/*   Updated: 2016/12/10 19:05:25 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/rtv1.h"

void	check_brillance_ombre(t_var *var)
{
	char	*tmp;

	if (!(tmp = parse_str(DOC, "brillance ", 1, var)))
		BRILLANCE = 1;
	else
	{
		if (ft_atof(tmp) == 1)
			BRILLANCE = 1;
		else
			BRILLANCE = 0;
		free(tmp);
	}
	if (!(tmp = parse_str(DOC, "ombre", 1, var)))
		OMBRE = 1;
	else
	{
		if (ft_atof(tmp) == 1)
			OMBRE = 1;
		else
			OMBRE = 0;
		free(tmp);
	}
}

void	check_origin2(t_var *var)
{
	char	*tmp;
	char	**tab;

	if (!(tmp = parse_str(OBJ_STR, "origin2 ", 0, var)))
		ft_exit("pas de cylindre origin2");
	else
	{
		tab = ft_strsplit(tmp, ' ');
		if (!tab[0] || !tab[1] || !tab[2])
			ft_exit("problem cylinder origin2");
		OBJ_ORIGIN2 = fill_vector(ft_atof(tab[0]), ft_atof(tab[1]),
				ft_atof(tab[2]));
		ft_free2tab(tab);
		free(tmp);
	}
}

void	check_cylinder_cone_origins(t_var *var)
{
	char	*tmp;
	char	**tab;

	if (!(tmp = parse_str(OBJ_STR, "origin1 ", 0, var)))
		ft_exit("pas de cylindre origin1");
	else
	{
		tab = ft_strsplit(tmp, ' ');
		if (!tab[0] || !tab[1] || !tab[2])
			ft_exit("problem cylinder origin1");
		OBJ_ORIGIN = fill_vector(ft_atof(tab[0]), ft_atof(tab[1]),
				ft_atof(tab[2]));
		ft_free2tab(tab);
		free(tmp);
	}
	check_origin2(var);
}
