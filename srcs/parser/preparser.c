/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:40:35 by fballest          #+#    #+#             */
/*   Updated: 2021/12/10 12:04:43 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_finish(char *prompt, t_cmd_info *cmd_info, t_pparse *pp)
{
	pp->aux[pp->j] = '\0';
	if ((pp->d_quotes > 0 && (pp->d_quotes % 2))
		|| (pp->s_quotes > 0 && (pp->s_quotes % 2)))
	{
		printf("minishell: syntax error\n");
		cmd_info->return_code = 3;
		return (NULL);
	}
	free (prompt);
	prompt = ft_strdup(pp->aux);
	free (pp->aux);
	free (pp);
	return (prompt);
}

void	check_doublequotes(char *prompt, t_pparse *pp)
{
	if (prompt[pp->i + 1] != '\"')
	{
		pp->d_quotes += 1;
		if (prompt[pp->i + 1] == '\''
			&& (pp->d_quotes == 0 || !(pp->d_quotes % 2)))
		{
			pp->s_quotes += 1;
			pp->i += 2;
		}
		else
			pp->aux[pp->j++] = prompt[pp->i++];
	}
	else
		pp->i += 2;
}

void	check_addletter(char *prompt, t_pparse *pp)
{
	pp->aux[pp->j++] = prompt[pp->i++];
	pp->aux[pp->j] = '\0';
}

char	*check_prompt_b(char *prompt, t_cmd_info *cmd_info, t_pparse *pp)
{
	prompt = expand_mayorminor(prompt, pp);
	if (!prompt)
	{
		cmd_info->return_code = 1;
		return (NULL);
	}
	free (pp->aux);
	pp->aux = ft_strdup(prompt);
	return (prompt);
}

char	*check_prompt(char *prompt, t_cmd_info *cmd_info)
{
	t_pparse	*pp;

	pp = ft_calloc(sizeof(t_pparse), 1);
	if (check_end_prompt(prompt, cmd_info, pp) == 1)
		return (NULL);
	pp->aux = ft_strdup(prompt);
	while (prompt[pp->i] != '\0')
	{
		if (prompt[pp->i] == '\'' && (pp->d_quotes == 0 || !(pp->d_quotes % 2)))
			check_simplequotes(prompt, pp);
		else if (prompt[pp->i] == '\"' && (pp->s_quotes == 0
				|| !(pp->s_quotes % 2)))
			check_doublequotes(prompt, pp);
		else if ((prompt[pp->i] == '>' || prompt[pp->i] == '<')
			&& ((pp->d_quotes == 0 || (pp->d_quotes % 2) == 0)
				&& (pp->s_quotes == 0 || (pp->s_quotes % 2) == 0)))
		{
			prompt = check_prompt_b(prompt, cmd_info, pp);
			if (!prompt)
				return (NULL);
		}
		else
			check_addletter(prompt, pp);
	}
	return (check_finish(prompt, cmd_info, pp));
}
