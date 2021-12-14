/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_initial_envs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:15:47 by rcabezas          #+#    #+#             */
/*   Updated: 2021/10/22 13:55:37 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_initial_envs(char **envs)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (envs[i])
	{
		if (!ft_strncmp("OLDPWD", envs[i], 7))
			x++;
		else if (!ft_strncmp("PWD=", envs[i], 4))
			x++;
		else if (!ft_strncmp("SHLVL=", envs[i], 6))
			x++;
		i++;
	}
	return (4 - x);
}

int	find_oldpwd(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		if (!ft_strncmp("OLDPWD", envs[i], 6))
			return (1);
		i++;
	}
	return (0);
}

int	find_pwd(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		if (!ft_strncmp("PWD", envs[i], 3))
			return (1);
		i++;
	}
	return (0);
}

int	find_shlvl(char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		if (!ft_strncmp("SHLVL", envs[i], 5))
			return (1);
		i++;
	}
	return (0);
}
