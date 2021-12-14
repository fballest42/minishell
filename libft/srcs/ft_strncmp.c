/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:28:40 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/06 21:56:38 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t				i;
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = (const unsigned char *)str1;
	s2 = (const unsigned char *)str2;
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1 != NULL && s2[i] != '\0' && i < n - 1)
		i++;
	return (s1[i] - s2[i]);
}
