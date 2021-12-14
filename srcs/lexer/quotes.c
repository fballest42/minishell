/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:02:06 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/09 10:28:18 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_quotes(t_env *env, t_parser *p, char c, t_cmd_info *cmd_info)
{
	int		j;

	p->i++;
	j = 0;
	while (p->prompt[p->i] != c && p->prompt[p->i + 1])
	{
		if (p->prompt[p->i] == '$' && c == '\"')
			expand_dollars(env, p, &j, cmd_info);
		if (p->prompt[p->i] == c)
			return ;
		set_next_char(p, &j);
	}
}

void	simple_quotes_after_char(t_parser *p, int *j)
{
	p->i++;
	while (p->prompt[p->i] && p->prompt[p->i] != '\'')
		set_next_char(p, j);
	p->i++;
}

void	double_quotes_after_char(t_parser *p, t_env *env,
	t_cmd_info *cmd_info, int *j)
{
	p->i++;
	while (p->prompt[p->i] && p->prompt[p->i] != '\"')
	{
		if (p->prompt[p->i] == '$')
			expand_dollars(env, p, j, cmd_info);
		if (p->prompt[p->i] == '$')
			continue ;
		set_next_char(p, j);
	}
	if (p->prompt[p->i] == '\"')
		p->i++;
}
