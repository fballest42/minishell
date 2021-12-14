/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:19:36 by fballest          #+#    #+#             */
/*   Updated: 2021/12/06 18:05:20 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*cmd_path(t_env *env, char *cmd)
{
	char	*path;
	char	*tmp;
	int		check_path;

	check_path = 0;
	tmp = NULL;
	path = cmd_path2(cmd, tmp, check_path, env);
	if (!path)
	{
		tmp = ft_strjoin(cmd, ": command not found\n");
		ft_putstr_fd(tmp, 2);
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	return (path);
}

int	execute_builtins(t_exe exe, t_env *env)
{
	int		ret;

	if (!ft_strcmp(exe.cmd, "echo"))
		ret = execute_echo(exe);
	if (!ft_strcmp(exe.cmd, "cd"))
		ret = execute_cd(exe, env);
	else if (!ft_strcmp(exe.cmd, "pwd"))
		ret = execute_pwd();
	else if (!ft_strcmp(exe.cmd, "env"))
		ret = execute_env(exe, env);
	else if (!ft_strcmp(exe.cmd, "export"))
		ret = execute_export(exe, env);
	else if (!ft_strcmp(exe.cmd, "unset"))
		ret = execute_unset(exe, env);
	else if (!ft_strcmp(exe.cmd, "exit"))
		ret = execute_exit(exe);
	return (ret);
}
