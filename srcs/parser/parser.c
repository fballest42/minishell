/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:27:54 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/06 21:53:34 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	fill_exe(t_cmd_info *cmd_info, int i)
{
	t_list	*tmp;
	int		arg;

	tmp = cmd_info->command_list;
	while (tmp)
	{
		arg = 0;
		while (tmp && ((t_node *)tmp->content)->types != PIPE)
		{
			if (((t_node *)tmp->content)->types == ARGUMENT && arg == 0)
				assign_cmd_from_argument(cmd_info, tmp, &arg, i);
			else if (((t_node *)tmp->content)->types == ARGUMENT && arg == 1)
			{
				assign_arguments_from_list(tmp, cmd_info->exe, i);
				while (count_arguments(tmp) - 1 > 0)
					tmp = tmp->next;
			}
			else if (((t_node *)tmp->content)->types == FILE_NAME)
				assign_fd_from_list(tmp, cmd_info->exe, i);
			tmp = tmp->next;
		}
		i++;
		if (tmp)
			tmp = tmp->next;
	}
}

static void	downcase_cmds(t_cmd_info *cmd_info)
{
	int	i;

	i = 0;
	while (i <= cmd_info->no_pipes && cmd_info->exe[++i].cmd)
		ft_strdowncase(cmd_info->exe[i].cmd);
}

void	parser(t_cmd_info *cmd_info)
{
	cmd_info->exe = ft_calloc(sizeof(t_exe), cmd_info->no_pipes + 2);
	fill_exe(cmd_info, 0);
	downcase_cmds(cmd_info);
}
