/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:08:30 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/10 12:07:07 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	leaks(void)
{
	system("leaks minishell");
}

char	*prompt_main(int argc, char **argv)
{
	char			*prompt;

	(void)argc;
	(void)argv;
	prompt = readline("\033[0;32mminishell - \033[0;0m");
	if (!prompt)
		exit(0);
	if (prompt[0] != '\0')
		add_history(prompt);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*env;
	t_cmd_info		*cmd_info;
	char			*prompt;

	cmd_info = ft_calloc(sizeof(t_cmd_info), 1);
	env = ft_calloc(sizeof(t_env), 1);
	take_envs(envp, env);
	while (1)
	{
		sig_init();
		prompt = prompt_main(argc, argv);
		if (prompt[0] != '\0')
		{
			prompt = check_prompt(prompt, cmd_info);
			if (!prompt)
				continue ;
			lexer(env, cmd_info, prompt);
			analyze_prompt(cmd_info, env);
			parser(cmd_info);
			execute(cmd_info, env);
			reset_values(cmd_info);
		}
		free(prompt);
	}
	return (0);
}
