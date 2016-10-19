/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstrstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 14:54:47 by atoulous          #+#    #+#             */
/*   Updated: 2016/10/19 14:56:22 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbstrstr(const char *big, const char *little)
{
	int		size;
	int		c;

	c = 0;
	size = ft_strlen(little);
	while (*big)
	{
		if (!(ft_strncmp(big, little, size)))
			c++;
		big++;
	}
	return (c);
}
