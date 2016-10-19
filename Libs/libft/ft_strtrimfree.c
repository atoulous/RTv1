/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 18:18:26 by atoulous          #+#    #+#             */
/*   Updated: 2016/10/19 18:19:01 by atoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimfree(char const *s)
{
	char	*new;
	size_t	i;
	size_t	start;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	if (!s[i])
	{
		if (!(new = ft_strnew(i)))
			return (NULL);
		return (new);
	}
	start = i;
	while (s[i])
		i++;
	while (i > 0 && (s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t'))
		i--;
	if (!(new = ft_strsub(s, start, i - start)))
		return (NULL);
	free((char *)s);
	return (new);
}
