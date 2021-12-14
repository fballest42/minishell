/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:30:36 by rcabezas          #+#    #+#             */
/*   Updated: 2019/11/13 18:42:11 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	char			m;
	unsigned char	*p;

	p = (unsigned char *)str;
	i = 0;
	m = c + 0;
	while (i < len)
	{
		p[i] = m;
		i++;
	}
	return (str);
}
