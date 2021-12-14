/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:11:07 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/09 14:15:17 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_take_envs_free(t_env *env)
{
	int		i;

	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
		{
			free(env->pwd);
			env->pwd = ft_strchr2(env->envp[i], '=');
		}
		if (ft_strncmp("OLDPWD=", env->envp[i], 7) == 0)
		{
			free(env->oldpwd);
			env->oldpwd = ft_strchr2(env->envp[i], '=');
		}
		i++;
	}
}

void	ft_change_env(t_env *env)
{
	int		i;
	char	**tmpenv;

	i = ft_matrixlen(env->envp);
	tmpenv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env->envp[i])
	{
		if (ft_strncmp("PWD=", env->envp[i], 4) == 0)
			tmpenv[i] = ft_strjoin("PWD=", env->pwd);
		else if (ft_strncmp("OLDPWD", env->envp[i], 6) == 0)
			tmpenv[i] = ft_strjoin("OLDPWD=", env->oldpwd);
		else
			tmpenv[i] = ft_strdup(env->envp[i]);
		i++;
	}
	tmpenv[i] = NULL;
	ft_freematrix(env->envp);
	env->envp = ft_matrixdup(tmpenv);
	ft_freematrix(tmpenv);
}

void	change_env_in_env_utils(char **newenv, t_env *env, int *i, int *j)
{
	newenv[(*i)] = ft_strdup(env->envp[(*j)]);
	free(env->envp[(*j)]);
	(*i)++;
	(*j)++;
}

char	**remove_env(t_env *env, char *erased)
{
	int		i;
	int		j;
	char	**newenv;

	i = 0;
	j = 0;
	i = ft_matrixlen(env->envp);
	newenv = malloc(sizeof(char *) * i);
	i = 0;
	while (env->envp[j])
	{
		if (!ft_strncmp(env->envp[j], erased, ft_strlen(erased)))
		{
			free(env->envp[j]);
			j++;
		}
		else
			change_env_in_env_utils(newenv, env, &i, &j);
	}
	newenv[i] = NULL;
	free(env->envp);
	return (newenv);
}

int	check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}
