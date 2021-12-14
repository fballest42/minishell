/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:40:35 by fballest          #+#    #+#             */
/*   Updated: 2021/12/10 12:00:48 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	expand_conditions(char *prompt, char *tmp, t_pparse *pp)
{
	int		z;

	z = 0;
	if ((prompt[pp->i] == '>' && prompt[pp->i + 1] == '>'
			&& prompt[pp->i + 2] == '>') || (prompt[pp->i] == '<'
			&& prompt[pp->i + 1] == '<' && prompt[pp->i + 2] == '<')
		|| (prompt[pp->i] == '>' && prompt[pp->i + 1] == '<')
		|| (prompt[pp->i] == '<' && prompt[pp->i + 1] == '>'))
		z = 666;
	else if (prompt[pp->i] == '>' && prompt[pp->i + 1] == '>')
		z = 2;
	else if (prompt[pp->i] == '<' && prompt[pp->i + 1] == '<')
		z = 2;
	else if (prompt[pp->i] == '>')
		z = 1;
	else if (prompt[pp->i] == '<')
		z = 1;
	else
		tmp[pp->j++] = prompt[pp->i++];
	return (z);
}

int	check_end_prompt(char *prompt, t_cmd_info *cmd_info, t_pparse *pp)
{
	int		len;
	int		i;

	len = ft_strlen(prompt);
	while (len > 0 && prompt[len - 1] && (prompt[len - 1] == ' '
			|| prompt[len - 1] == '\t'))
		len--;
	if (len == 0)
		return (0);
	i = check_before_pipes(prompt, cmd_info, len);
	if (i > 0 || (len > 0 && (prompt[len - 1] == '|' || prompt[len - 1] == '>'
				|| prompt[len - 1] == '<')))
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 57);
		cmd_info->return_code = 258;
		free (prompt);
		prompt = NULL;
		free (pp);
		return (1);
	}
	return (0);
}

void	check_simplequotes(char *prompt, t_pparse *pp)
{
	if (prompt[pp->i + 1] != '\'')
	{
		pp->s_quotes += 1;
		if (prompt[pp->i + 1] == '\"'
			&& (pp->s_quotes == 0 || !(pp->s_quotes % 2)))
		{
			pp->d_quotes += 1;
			pp->i += 2;
		}
		else
			pp->aux[pp->j++] = prompt[pp->i++];
	}
	else
		pp->i += 2;
}
