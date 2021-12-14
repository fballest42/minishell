/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:04:35 by rcabezas          #+#    #+#             */
/*   Updated: 2021/05/17 18:55:50 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_number(const char *str, int min, int max, int i)
{
	int	j;

	j = 0;
	while (str[i] > 47 && str[i] < 58)
	{
		j = j * 10 + (str[i] - '0');
		i++;
	}
	if (min > 1 || max > 1 || min + max > 1)
		j = 0;
	else if (min == 1)
		j = -j;
	if (j <= -469762049)
		return (-1);
	if (j >= 469762049)
		return (0);
	return (j);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	min;
	int	max;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	min = 0;
	max = 0;
	while (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			min++;
		else if (str[i] == 43)
			max++;
		i++;
	}
	return (ft_number(str, min, max, i));
}
