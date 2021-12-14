/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 13:52:31 by rcabezas          #+#    #+#             */
/*   Updated: 2021/09/23 11:27:25 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (!ptr)
		return (ft_calloc(size, 1));
	if (size == 0)
		return (ptr);
	new = ft_calloc(size, 1);
	ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}
