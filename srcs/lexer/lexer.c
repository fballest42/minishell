/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:01:26 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/06 17:58:14 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	quotes_in_chars(t_parser *p, t_env *env, t_cmd_info *cmd_info, int *j)
{
	int	comillas;

	comillas = 0;
	if (p->prompt[p->i] == '\'')
	{
		simple_quotes_after_char(p, j);
		comillas = 1;
	}
	else if (p->prompt[p->i] == '\"')
	{
		comillas = 2;
		double_quotes_after_char(p, env, cmd_info, j);
	}
	return (comillas);
}

void	set_next_char(t_parser *p, int *j)
{
	if (!p->prompt[p->i])
		return ;
	p->word = ft_realloc(p->word, (ft_strlen(p->word) + 2));
	p->word[*j] = p->prompt[p->i];
	(*j)++;
	p->word[*j] = '\0';
	if (p->prompt[p->i])
		p->i++;
}

int	check_dollar_to_print(t_parser *p)
{
	if (!p->prompt[p->i - 1] || !p->prompt[p->i])
		return (0);
	if (p->prompt[p->i] == '$'
		&& (p->prompt[p->i + 1]
			&& p->prompt[p->i + 1] != '\"'
			&& p->prompt[p->i + 1] != '\''
			&& p->prompt[p->i + 1] != ' '
			&& p->prompt[p->i + 1] != '$'))
		return (1);
	return (0);
}

int	parse_simple_chars(t_env *env, t_parser *p, t_cmd_info *cmd_info, int j)
{
	int	comillas;

	comillas = 0;
	while (p->prompt[p->i] != '\0' && p->prompt[p->i] != ' ')
	{
		if (p->prompt[p->i] == '\'' || p->prompt[p->i] == '\"')
			comillas = quotes_in_chars(p, env, cmd_info, &j);
		else
		{
			if (p->prompt[p->i] == '$')
			{
				if (p->prompt[p->i + 1] != '\'' && p->prompt[p->i + 1] != '\"')
					expand_dollars(env, p, &j, cmd_info);
				else
				{
					parse_quotes(env, p, p->prompt[++(p->i)], cmd_info);
					return (comillas);
				}
				if (check_dollar_to_print(p))
					continue ;
			}
			set_next_char(p, &j);
		}
	}
	return (comillas);
}

void	lexer(t_env *env, t_cmd_info *cmd_info, char *prompt)
{
	t_parser	*p;
	int			prompt_len;

	p = ft_calloc(sizeof(t_parser), 1);
	p->prompt = ft_strdup(prompt);
	prompt_len = (int)ft_strlen(prompt);
	while (p->i < prompt_len)
		word_analyzer(p, env, cmd_info);
	free(p->prompt);
	free (p);
}
