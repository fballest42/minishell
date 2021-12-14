/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/12/09 14:03:07 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*heredoc_expander(const char *file, char *tmp, t_env *env, t_here *h)
{
	h->i = 0;
	h->z = 0;
	while (tmp[h->i])
		if (tmp[h->i++] == '$')
			h->j++;
	while (h->j > 0)
	{
		heredoc_expander_init(tmp, h);
		heredoc_expander_dollar(tmp, env, h);
		heredoc_expander_finish(tmp, h);
		tmp = heredoc_expander_free(tmp, h);
		h->j--;
	}
	if (!ft_strncmp(file, tmp, ft_strlen(file) + 1))
	{
		free (tmp);
		free (h);
		return (NULL);
	}
	return (tmp);
}

char	*heredoc_bucle_disclaimer(const char *file, char *tmp,
	t_env *env, t_here *h)
{
	if (h->comillas == 0)
		tmp = heredoc_expander(file, tmp, env, h);
	else
		tmp = ft_strdup(tmp);
	return (tmp);
}

void	ft_heredoc_bucle_b(const char *file, char *tmp, t_env *env, t_here *h)
{
	while (1)
	{
		tmp = readline("> ");
		if (tmp && (tmp[0] != '\0' || ft_strlen(tmp) == 0))
		{
			if (!ft_strncmp(file, tmp, ft_strlen(file) + 1))
			{
				free (tmp);
				free (h);
				break ;
			}
			else
			{
				tmp = heredoc_bucle_disclaimer(file, tmp, env, h);
				heredoc_writer(tmp, h);
			}
		}
		else
			free (tmp);
	}
}

void	ft_heredoc_bucle(const char *file, t_env *env, int comillas, int fd)
{
	char	*tmp;
	t_here	*h;

	tmp = NULL;
	h = ft_calloc(sizeof(t_here), 1);
	h->fd = fd;
	h->comillas = comillas;
	ft_heredoc_bucle_b(file, tmp, env, h);
}

int	ft_heredoc(char *file, t_cmd_info *cmd_info, t_env *env, int comillas)
{
	char	*filename;
	int		fd;

	filename = "/private/tmp/hd_ms2021.txt";
	if (!access(filename, W_OK))
		unlink(filename);
	fd = open(filename, O_RDWR | O_CREAT, S_IRWXU);
	if (fd < 0)
	{
		cmd_info->return_code = errno;
		perror("minishell: ");
		return (0);
	}
	else
	{
		ft_heredoc_bucle(file, env, comillas, fd);
		close (fd);
		fd = ft_indirection(filename, cmd_info);
	}
	return (fd);
}
