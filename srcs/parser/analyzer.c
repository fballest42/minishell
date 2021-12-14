/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:32:58 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/09 15:07:03 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	analyze_prompt(t_cmd_info *cmd_info, t_env *env)
{
	t_list	*aux;
	t_type	type;

	aux = cmd_info->command_list;
	while (aux)
	{
		if (((t_node *)aux->content)->types > 1
			&& ((t_node *)aux->content)->types < 6)
		{
			type = ((t_node *)aux->content)->types;
			if (aux->next)
				aux = aux->next;
			if (((t_node *)aux->content)->types == PIPE)
			{
				write(2, "minishell: syntax error near unexpected token\n", 47);
				cmd_info->return_code = 258;
				return ;
			}
			((t_node *)aux->content)->types = FILE_NAME;
			ft_manageredirections(cmd_info, env, ((t_node *)aux->content),
				type);
		}
		aux = aux->next;
	}
}
