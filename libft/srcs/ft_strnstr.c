/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:29:47 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/06 21:56:24 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*big;

	big = (char *)haystack;
	i = 0;
	j = 0;
	if (ft_strlen(needle) == 0)
		return (big);
	if (ft_strlen(haystack) == 0)
		return (0);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return (big + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}
