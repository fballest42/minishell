/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocwrite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 13:47:42 by fballest          #+#    #+#             */
/*   Updated: 2021/12/06 22:19:49 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc_writer(char *tmp, t_here *h)
{
	if (!tmp || ft_strlen(tmp) == 0)
		write (h->fd, "\n", 1);
	else
	{
		write (h->fd, tmp, ft_strlen(tmp));
		write (h->fd, "\n", 1);
	}
	free (tmp);
}
