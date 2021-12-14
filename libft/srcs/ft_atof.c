/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 12:20:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/03/11 12:10:11 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_norm_1(char *str, int i, int fac)
{
	if (str[i] == '-')
		fac = -1;
	return (fac);
}

static int	skip_norm_2(int i, int fac)
{
	if (fac == -1)
		i++;
	return (i);
}

float	ft_atof(char *str)
{
	float	atof;
	int		atoi;
	int		i;
	int		fac;

	fac = 1;
	atof = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	fac = skip_norm_1(str, i, fac);
	atoi = ft_atoi(str);
	i = ft_numlen(atoi);
	i = skip_norm_2(i, fac);
	if (str[i] != '.')
		return (atoi);
	i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		fac *= 10;
		atof = atof * 10 + str[i] - 48;
		i++;
	}
	atof = atof / fac;
	return (atoi + atof);
}
