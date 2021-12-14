/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:00:10 by rcabezas          #+#    #+#             */
/*   Updated: 2019/12/10 15:37:59 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	i = start;
	j = 0;
	a = (char *)malloc(len + 1);
	if (!a)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	while (j < len)
	{
		a[j] = s[i];
		i++;
		j++;
	}
	a[j] = '\0';
	return (a);
}
