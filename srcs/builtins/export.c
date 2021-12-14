/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 10:39:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/10 12:18:58 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_envs_export(char **envs)
{
	int		i;
	char	**ordered;
	char	*name;
	char	*value;

	ordered = order_envs(envs);
	i = 0;
	while (ordered[i])
	{
		name = ft_strtok(ordered[i], '=');
		value = ft_strchr2(ordered[i], '=');
		if (value)
			printf("%s=\"%s\"\n", name, value);
		else
			printf("%s=\"\"\n", name);
		free (name);
		i++;
	}
	ft_freematrix(ordered);
}

static char	**export_checks(t_env *env, char *str, char **ret, int i)
{
	if (!check_env(str, ret))
		ret[i++] = ft_strdup(str);
	if (ft_strcmp(str, "PATH="))
		assign_path(env, str);
	ret[i] = NULL;
	return (ret);
}

char	**add_string_to_array(t_env *env, char **arr, char *str)
{
	char	**ret;
	char	*name;
	char	*aux;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (ft_matrixlen(arr) + 2));
	while (arr[i])
	{
		aux = ft_strtok(arr[i], '=');
		name = ft_strjoin(aux, "=");
		if (!ft_strncmp(name, str, ft_strlen(name)) && ft_strchr(str, '='))
			ret[i] = ft_strdup(str);
		else
			ret[i] = ft_strdup(arr[i]);
		ret[++i] = NULL;
		free(name);
		free(aux);
	}
	ret = export_checks(env, str, ret, i);
	ft_freematrix(arr);
	arr = NULL;
	return (ret);
}

int	execute_export(t_exe exe, t_env *env)
{
	int	i;

	if (ft_matrixlen(exe.args) == 0)
	{
		print_envs_export(env->envp);
		return (0);
	}
	i = 0;
	while (exe.args[i])
	{
		env->envp = add_string_to_array(env, env->envp,
				exe.args[i]);
		i++;
	}
	return (0);
}
