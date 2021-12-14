/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocexpander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fballest <fballest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:01:44 by fballest          #+#    #+#             */
/*   Updated: 2021/12/06 22:19:37 by fballest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*fill_env(char *dollar, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (ft_strcmp("", dollar))
	{
		while (env->envp[i])
		{
			if (!ft_strncmp(env->envp[i], dollar, ft_strlen(dollar)))
				tmp = ft_strdup(ft_strchr2(env->envp[i], '='));
			i++;
		}
	}
	free (dollar);
	if (!tmp)
		return (NULL);
	return (tmp);
}

void	heredoc_expander_init(char *tmp, t_here *h)
{
	h->i = 0;
	while (tmp[h->i] && tmp[h->i] != '$')
	{
		if (!h->str1)
			h->str1 = ft_strdup("");
		h->str1 = ft_realloc(h->str1, (ft_strlen(h->str1) + 2));
		h->str1[h->i] = tmp[h->i];
		h->i++;
		h->str1[h->i] = '\0';
	}
	h->z = 0;
}

void	heredoc_expander_dollar(char *tmp, t_env *env, t_here *h)
{
	if (tmp[h->i] && (tmp[h->i] == '$' && (tmp[h->i + 1] != '\''
				&& tmp[h->i + 1] != '\"' && tmp[h->i + 1] != ' ')))
	{
		h->i++;
		while (tmp[h->i] && (tmp[h->i] != '\''
				&& tmp[h->i] != '\"' && tmp[h->i] != ' '))
		{
			if (!h->str2)
				h->str2 = ft_strdup("");
			h->str2 = ft_realloc(h->str2, (ft_strlen(h->str2) + 2));
			h->str2[h->z++] = tmp[h->i++];
			h->str2[h->z] = '\0';
		}
		h->str2 = fill_env(h->str2, env);
	}
	else
	{
		if (!h->str2)
			h->str2 = ft_strdup("");
		h->str2 = ft_realloc(h->str2, (ft_strlen(h->str2) + 2));
		h->str2[h->z++] = tmp[h->i++];
		h->str2[h->z] = '\0';
	}
}

void	heredoc_expander_finish(char *tmp, t_here *h)
{
	while (tmp[h->i])
	{
		if (!h->str2)
		{
			h->str2 = ft_strdup("");
			h->z = 0;
		}
		else
			while (h->str2[h->z])
				h->z++;
		h->str2 = ft_realloc(h->str2, h->z + 2);
		h->str2[h->z++] = tmp[h->i++];
		h->str2[h->z] = '\0';
	}
	if (!h->str1)
		h->str1 = ft_strdup("");
	free (tmp);
	tmp = NULL;
}

char	*heredoc_expander_free(char *tmp, t_here *h)
{
	if (!h->str2 || ft_strlen(h->str2) == 0)
		tmp = ft_strdup(h->str1);
	else
	{
		tmp = ft_strjoin(h->str1, h->str2);
		free (h->str2);
		h->str2 = NULL;
	}
	free (h->str1);
	h->str1 = NULL;
	return (tmp);
}
