/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 09:00:17 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/07 09:00:54 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	del(void *node)
{
	free(((t_node *)node)->prompts);
	((t_node *)node)->prompts = NULL;
	((t_node *)node)->types = 0;
	free((t_node *)node);
}

void	free_exe(t_cmd_info *cmd_info)
{
	int	i;

	i = 0;
	while (i <= cmd_info->no_pipes)
	{
		free(cmd_info->exe[i].cmd);
		if (cmd_info->exe[i].args)
			ft_freematrix(cmd_info->exe[i].args);
		i++;
	}
}

void	reset_values(t_cmd_info *cmd_info)
{
	ft_lstclear(&cmd_info->command_list, del);
	free_exe(cmd_info);
	free(cmd_info->exe);
	cmd_info->no_pipes = 0;
}
