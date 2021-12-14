/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:27:30 by rcabezas          #+#    #+#             */
/*   Updated: 2019/11/13 19:55:51 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	ch;
	char	*p;
	int		i;
	int		j;

	i = 0;
	p = (char *)str;
	ch = c + 0;
	j = -1;
	if (c == '\0')
		return (ft_strchr(str, '\0'));
	while (p[i] != '\0')
	{
		if (p[i] == ch)
			j = i;
		i++;
	}
	if (j != -1)
		return (p + j);
	return (0);
}
