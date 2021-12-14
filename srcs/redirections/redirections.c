/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/12/09 12:39:27 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_directory(char *filename, t_cmd_info *cmd_info)
{
	DIR		*dir;

	dir = opendir(filename);
	if (dir)
	{
		closedir(dir);
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : is a directory\n", 19);
		return (cmd_info->return_code = -126);
	}
	return (0);
}

int	ft_append(char *filename, t_cmd_info *cmd_info)
{
	int		fd;

	fd = 0;
	if (check_directory(filename, cmd_info) < 0)
		return (cmd_info->return_code);
	if (!access(filename, W_OK))
		fd = open(filename, O_RDWR | O_APPEND);
	else
		fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		write(2, "minishell: ", 12);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		return (cmd_info->return_code = -1);
	}
	return (fd);
}

int	ft_indirection(char *filename, t_cmd_info *cmd_info)
{
	int		fd;

	fd = 0;
	if (check_directory(filename, cmd_info) < 0)
		return (cmd_info->return_code);
	if (access(filename, R_OK))
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		return (cmd_info->return_code = -1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		return (cmd_info->return_code = -1);
	}
	return (fd);
}

int	ft_redirection(char *filename, t_cmd_info *cmd_info)
{
	int		fd;

	fd = 0;
	if (check_directory(filename, cmd_info) < 0)
		return (cmd_info->return_code);
	if (!access(filename, R_OK))
		unlink(filename);
	fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		write(2, "minishel: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, " : No such file or directory\n", 30);
		return (cmd_info->return_code = -1);
	}
	return (fd);
}

void	ft_manageredirections(t_cmd_info *cmd_info, t_env *env, t_node *node,
		t_type type)
{
	if (type == HERE_DOC)
	{
		if (node->prompts && !ft_strlen(node->prompts))
		{
			write (2, "minishell: Non-existing enviroment variable\n", 45);
			cmd_info->return_code = 1;
			return ;
		}
		node->fd_in = ft_heredoc(node->prompts, cmd_info, env, node->comillas);
	}
	else if (type == INDIRECTION)
		node->fd_in = ft_indirection(node->prompts, cmd_info);
	else if (type == REDIRECTION)
		node->fd_out = ft_redirection(node->prompts, cmd_info);
	else if (type == APPEND)
		node->fd_out = ft_append(node->prompts, cmd_info);
}
