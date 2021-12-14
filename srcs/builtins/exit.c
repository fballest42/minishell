/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:13:53 by fballest          #+#    #+#             */
/*   Updated: 2021/11/23 10:10:44 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	alpha_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	alpha_exit(char *alpha)
{
	write(2, alpha, ft_strlen(alpha));
	write(2, ": numeric argument required\n", 29);
	exit(255);
}

void	normal_exit(char *n)
{
	int	ret;

	ret = ft_atoi(n);
	exit(ret);
}

int	execute_exit(t_exe exe)
{
	int		nargs;

	printf("exit\n");
	nargs = ft_matrixlen(exe.args);
	if (nargs == 0)
		exit(0);
	if (alpha_in_string(exe.args[0]))
		alpha_exit(exe.args[0]);
	if (nargs > 1)
	{
		write(2, "exit: too many arguments\n", 26);
		return (1);
	}
	else
		normal_exit(exe.args[0]);
	return (0);
}
