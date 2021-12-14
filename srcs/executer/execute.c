/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:15:28 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/07 08:40:52 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_arguments(t_list *tmp)
{
	t_list	*aux;
	int		i;

	aux = tmp;
	i = 0;
	while (((t_node *)aux) && ((t_node *)aux->content)->types == ARGUMENT)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}

char	**assign_arguments_for_execve(t_list *tmp)
{
	char	**ret;
	int		i;
	int		narg;

	narg = count_arguments(tmp);
	ret = NULL;
	ret = malloc(sizeof(char *) * (narg + 1));
	i = 0;
	while (i < narg)
	{
		ret[i] = ft_strdup(((t_node *)tmp->content)->prompts);
		tmp = tmp->next;
		i++;
		ret[i] = NULL;
	}
	return (ret);
}

void	execute(t_cmd_info *cmd_info, t_env *env)
{
	if (cmd_info->no_pipes == 0)
		cmd_info->return_code = execute_simple_commands(cmd_info, env);
	else
		cmd_info->return_code = execute_pipes(cmd_info, env);
}

char	*cmd_path2(char *cmd, char *tmp, int check_path, t_env *env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (env->paths && env->paths[i])
	{
		tmp = ft_strjoin(env->paths[i], cmd);
		check_path = access(tmp, X_OK);
		if (check_path < 0)
		{
			free(tmp);
			i++;
		}
		else
		{
			path = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
			break ;
		}
	}
	return (path);
}
