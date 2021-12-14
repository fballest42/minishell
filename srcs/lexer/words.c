/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:43:56 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/09 14:45:04 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	quote_management(t_cmd_info *cmd_info, t_env *env, t_parser *p, char c)
{
	parse_quotes(env, p, c, cmd_info);
	if (p->prompt[p->i] == c && p->prompt[p->i + 1]
		&& p->prompt[p->i + 1] != ' ')
	{
		p->i++;
		parse_simple_chars(env, p, cmd_info, ft_strlen(p->word));
	}
}

void	word_analyzer(t_parser *p, t_env *env, t_cmd_info *cmd_info)
{
	int	comillas;

	comillas = 0;
	p->word = ft_calloc(sizeof(char), 1);
	while (p->prompt[p->i] == ' ')
		p->i++;
	if (p->prompt[p->i] == '\'')
	{
		comillas = 1;
		quote_management(cmd_info, env, p, '\'');
	}
	else if (p->prompt[p->i] == '\"')
	{
		comillas = 2;
		quote_management(cmd_info, env, p, '\"');
	}
	else
		comillas = parse_simple_chars(env, p, cmd_info, 0);
	add_word_to_list(&cmd_info->command_list, cmd_info, p->word, comillas);
	free(p->word);
	p->i++;
}

void	assign_types(t_cmd_info *cmd_info, char *word, int comillas,
	t_node *node)
{
	if (!ft_strncmp(word, "<<", 2) && !comillas)
		node->types = HERE_DOC;
	else if (!ft_strncmp(word, ">>", 2) && !comillas)
		node->types = APPEND;
	else if (!ft_strncmp(word, "<", 1) && !comillas)
		node->types = INDIRECTION;
	else if (!ft_strncmp(word, ">", 1) && !comillas)
		node->types = REDIRECTION;
	else if (!ft_strncmp(word, "|", 1) && !comillas)
	{
		node->types = PIPE;
		cmd_info->no_pipes++;
	}
	else
	{
		node->types = ARGUMENT;
		if (comillas > 0)
			node->comillas = comillas;
	}
}

void	add_word_to_list(t_list **list, t_cmd_info *cmd_info, char *word,
			int comillas)
{
	t_node	*node;

	if (ft_strlen(word) == 0)
		return ;
	node = ft_calloc(sizeof(t_node), 1);
	node->prompts = ft_strdup(word);
	assign_types(cmd_info, word, comillas, node);
	ft_lstadd_back(list, ft_lstnew(node));
}
