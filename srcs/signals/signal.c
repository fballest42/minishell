/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:50:24 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/09 13:32:49 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	negligent_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_line_buffer[0] = '\0';
	rl_point = 0;
	rl_end = 0;
	rl_redisplay();
	return ;
}

void	sig_quit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	sig_init(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
