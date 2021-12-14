/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:55:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/09 14:41:51 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parent_cleanning(char *path, char **exeggutor,
	int saved_stdin, int saved_stdout)
{
	negligent_parent();
	free(path);
	ft_freematrix(exeggutor);
	restore_fds(saved_stdin, saved_stdout);
}

int	execute_execve_on_simple_commands(t_cmd_info *cmd_info, t_env *env,
	int saved_stdin, int saved_stdout)
{
	char	*path;
	int		pid;
	int		j;
	char	**exeggutor;

	j = 0;
	path = cmd_path(env, cmd_info->exe[0].cmd);
	if (check_dir_error(path, saved_stdin, saved_stdout))
		return (126);
	if (!path)
	{
		restore_fds(saved_stdin, saved_stdout);
		return (cmd_info->return_code = 127);
	}
	exeggutor = assign_arguments_with_cmd(cmd_info->exe[0]);
	pid = fork();
	if (pid == 0)
		child_signal(), execve(path, exeggutor, env->envp);
	else
	{
		parent_cleanning(path, exeggutor, saved_stdin, saved_stdout);
		waitpid(pid, &j, 0);
	}
	return (j % 255);
}

int	execute_simple_commands(t_cmd_info *cmd_info, t_env *env)
{
	int				saved_stdin;
	int				saved_stdout;

	if (cmd_info->exe[0].fd_in < 0 || cmd_info->exe[0].fd_out < 0)
		return (1);
	if (!cmd_info->exe[0].cmd)
		return (0);
	manage_fds(cmd_info->exe[0], &saved_stdin, &saved_stdout);
	if (check_builtin(cmd_info->exe[0].cmd))
	{
		cmd_info->return_code = execute_builtins(cmd_info->exe[0], env);
		restore_fds(saved_stdin, saved_stdout);
		return (cmd_info->return_code);
	}
	else
		return (execute_execve_on_simple_commands(cmd_info, env,
				saved_stdin, saved_stdout));
}
