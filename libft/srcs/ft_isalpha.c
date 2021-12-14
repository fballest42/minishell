/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:39:23 by rcabezas          #+#    #+#             */
/*   Updated: 2021/06/07 21:01:13 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	int	x;

	x = 0;
	if (c > 64 && c < 91)
		x = 1;
	else if (c > 96 && c < 123)
		x = 1;
	else
		x = 0;
	return (x);
}
