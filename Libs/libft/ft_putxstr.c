/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putxstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/26 16:17:49 by atoulous          #+#    #+#             */
/*   Updated: 2016/10/26 16:30:39 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putxstr(char *str1, char *str2, char *str3)
{
	str1 ? ft_putendl(str1) : 0;
	str2 ? ft_putendl(str2) : 0;
	str3 ? ft_putendl(str3) : 0;
}
