/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:34:56 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/19 01:59:18 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_after_know_flag(int n, t_exe exe, int jump)
{
	int	i;

	if (n == 1)
	{
		i = jump;
		while (exe.args[i])
		{
			printf("%s", exe.args[i]);
			if (exe.args[i + 1])
				printf(" ");
			i++;
		}
	}
	else
	{
		i = 0;
		while (exe.args[i])
		{
			printf("%s ", exe.args[i]);
			i++;
		}
		printf("\n");
	}
}

int	execute_echo(t_exe exe)
{
	int		i;
	int		j;
	int		n;

	if (!exe.args)
	{
		printf("\n");
		return (0);
	}
	n = 0;
	i = 0;
	while (exe.args[i] && !ft_strncmp(exe.args[i], "-n", 2))
	{
		j = 1;
		while (exe.args[i][j + 1]
			&& (exe.args[i][j + 1] == 'n'))
			j++;
		if (exe.args[i][j + 1])
			break ;
		else
			n = 1;
		i++;
	}
	print_after_know_flag(n, exe, i);
	return (0);
}
