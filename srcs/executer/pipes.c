/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:20:01 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/09 14:38:56 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parent_management(int read_pipe, int write_pipe[2])
{
	negligent_parent();
	if (read_pipe)
		close(read_pipe);
	if (write_pipe[WRITE_END] != STDOUT_FILENO)
		close(write_pipe[WRITE_END]);
}

static int	check_dir_error_pipes(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		write(2, "minishell: ", 12);
		write(2, path, ft_strlen(path));
		write(2, ": is a directory\n", 18);
		return (1);
	}
	else
		return (0);
}

void	pipe_execution(t_exe exe, int read_pipe, int write_pipe[2], t_env *env)
{
	pid_t	pid;
	char	*path;
	char	**exeggutor;

	if (check_dir_error_pipes(exe.cmd))
		return ;
	pid = fork();
	if (pid == 0)
	{
		child_signal();
		manage_read_fd(exe, read_pipe);
		close(write_pipe[READ_END]);
		manage_write_fd(exe, write_pipe);
		if (check_builtin(exe.cmd))
		{
			execute_builtins(exe, env);
			exit(EXIT_SUCCESS);
		}
		path = cmd_path(env, exe.cmd);
		exeggutor = assign_arguments_with_cmd(exe);
		execve(path, exeggutor, env->envp);
	}
	else
		parent_management(read_pipe, write_pipe);
}

int	waiting_room(int no_pipes)
{
	int	i;
	int	j;

	i = 0;
	while (i <= no_pipes)
	{
		waitpid(-1, &j, 0);
		i++;
	}
	return (j);
}

int	execute_pipes(t_cmd_info *cmd_info, t_env *env)
{
	int	i;
	int	write_pipe[2];
	int	read_pipe;

	i = 0;
	read_pipe = 0;
	while (i <= cmd_info->no_pipes)
	{
		if (i != cmd_info->no_pipes)
			pipe(write_pipe);
		else
			write_pipe[WRITE_END] = STDOUT_FILENO;
		pipe_execution(cmd_info->exe[i], read_pipe, write_pipe, env);
		read_pipe = write_pipe[READ_END];
		i++;
	}
	return (waiting_room(cmd_info->no_pipes));
}
