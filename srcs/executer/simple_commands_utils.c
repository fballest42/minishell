/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:05:35 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/09 13:06:43 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_dir_error(char *path, int saved_stdin, int saved_stdout)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		restore_fds(saved_stdin, saved_stdout);
		write(2, "minishell: ", 12);
		write(2, path, ft_strlen(path));
		write(2, ": is a directory\n", 18);
		free(path);
		return (1);
	}
	else
		return (0);
}

char	**assign_arguments_with_cmd(t_exe exe)
{
	char	**exeggutor;
	int		i;

	exeggutor = ft_calloc(sizeof(char *), (ft_matrixlen(exe.args) + 2));
	exeggutor[0] = ft_strdup(exe.cmd);
	i = 0;
	while (i < ft_matrixlen(exe.args))
	{
		i++;
		exeggutor[i] = ft_strdup(exe.args[i - 1]);
	}
	return (exeggutor);
}
