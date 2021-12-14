/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 22:01:42 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/14 12:50:41 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matrixdup(char **arr)
{
	int		i;
	char	**ret;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_matrixlen(arr) + 1));
	while (arr[i])
	{
		ret[i] = ft_strdup(arr[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
