/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:00:59 by rcabezas          #+#    #+#             */
/*   Updated: 2019/11/13 18:56:02 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*p;
	char	*q;

	p = (char *)dst;
	q = (char *)src;
	while (n--)
	{
		*p = *q;
		if (*q == (char)c)
		{
			dst++;
			return (dst);
		}
		dst++;
		p++;
		q++;
	}
	return (0);
}
