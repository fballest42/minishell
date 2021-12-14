/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:22:03 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/25 09:23:30 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	assign_arguments_from_list(t_list *tmp, t_exe *exe, int n)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (count_arguments(tmp) + 1));
	i = 0;
	while (tmp && ((t_node *)tmp->content)->types == ARGUMENT)
	{
		args[i] = ft_strdup(((t_node *)tmp->content)->prompts);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	exe[n].args = ft_matrixdup(args);
	ft_freematrix(args);
}

void	assign_cmd_from_argument(t_cmd_info *cmd_info, t_list *tmp,
			int *arg, int i)
{
	cmd_info->exe[i].cmd
		= ft_strdup(((t_node *)tmp->content)->prompts);
	*arg = 1;
}

void	assign_fd_from_list(t_list *tmp, t_exe *exe, int n)
{
	if (((t_node *)tmp->content)->fd_in)
		exe[n].fd_in = ((t_node *)tmp->content)->fd_in;
	if (((t_node *)tmp->content)->fd_out)
		exe[n].fd_out = ((t_node *)tmp->content)->fd_out;
}
