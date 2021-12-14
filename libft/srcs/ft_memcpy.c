/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:47:29 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/06 21:55:41 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*p;
	const char	*q;

	p = dst;
	q = src;
	if (*p == '\0' && *q == '\0')
		return (dst);
	else
	{
		while (n--)
			*p++ = *q++;
		return (dst);
	}
}
