/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:40:58 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/10 12:17:04 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	check_util_envs_for_unset(char *variable, t_env *env)
{
	if (!ft_strncmp(variable, "PWD", ft_strlen(variable)))
		env->pwd = NULL;
	else if (!ft_strncmp(variable, "OLDPWD", ft_strlen(variable)))
		env->oldpwd = NULL;
	else if (!ft_strncmp(variable, "PATH", ft_strlen(variable)))
	{
		ft_freematrix(env->paths);
		env->paths = NULL;
	}
	else if (!ft_strncmp(variable, "HOME", ft_strlen(variable)))
		env->home = NULL;
	else if (!ft_strncmp(variable, "USER", ft_strlen(variable)))
		env->user = NULL;
}

static char	*check_nums_in_unset(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (NULL);
	while (args[i])
	{
		if (ft_isdigit(args[i][0]))
			return (args[i]);
		i++;
	}
	return (NULL);
}

static char	**save_envs(char **args)
{
	char	**ret;
	int		i;

	i = ft_matrixlen(args);
	ret = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (args[i])
	{
		ret[i] = ft_strdup(args[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	execute_unset(t_exe exe, t_env *env)
{
	int		i;
	char	**variables;
	char	*error;

	if (!exe.args)
		return (0);
	error = check_nums_in_unset(exe.args);
	if (error)
	{
		write(2, error, ft_strlen(error));
		write(2, "`\': not a valid identifier\n", 28);
		return (1);
	}
	variables = save_envs(exe.args);
	i = 0;
	while (variables[i])
	{
		check_util_envs_for_unset(variables[i], env);
		if (check_env(variables[i], env->envp))
			env->envp = remove_env(env, variables[i]);
		i++;
	}
	ft_freematrix(variables);
	return (0);
}
