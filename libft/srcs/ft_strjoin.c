/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:16:17 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/11 12:40:18 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	i;
	size_t	j;

	if (!(s1 && s2))
		return (0);
	a = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!a)
		return (0);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		a[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		a[i] = s2[j];
		i++;
		j++;
	}
	a[i] = '\0';
	return (a);
}
