/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:38:39 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/16 15:03:38 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_env(t_exe exe, t_env *env)
{
	int		i;

	if (ft_matrixlen(exe.args) > 0)
	{
		write(2, exe.args[0], ft_strlen(exe.args[0]));
		write(2, ": No such file or directory\n", 28);
		return (127);
	}
	else
	{
		i = 0;
		while (env->envp[i])
		{
			if (ft_strchr(env->envp[i], '='))
				printf("%s\n", env->envp[i]);
			i++;
		}
	}
	return (0);
}
