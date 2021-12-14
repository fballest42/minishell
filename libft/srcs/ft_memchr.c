/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:12:44 by rcabezas          #+#    #+#             */
/*   Updated: 2019/11/13 20:04:37 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*p;
	char	ch;
	size_t	i;

	p = (char *)s;
	ch = c;
	i = 0;
	while (i < n)
	{
		if (p[i] == ch)
			return (p + i);
		i++;
	}
	return (0);
}
