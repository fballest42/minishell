/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:09:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/11 12:12:26 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*a;

	if (nitems == 0 || size == 0)
		nitems = size - 1;
	a = (char *)malloc(nitems * size);
	if (!a)
		return (0);
	ft_bzero(a, nitems * size);
	return (a);
}
