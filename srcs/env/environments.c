/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:26:38 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/02 22:00:17 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strchr2(const char *str, char c)
{
	int				i;
	unsigned char	ch;
	char			*p;

	i = 0;
	p = (char *)str;
	ch = c + '\0';
	while (p[i] != '\0')
	{
		if (p[i] == ch)
			return (p + i + 1);
		i++;
	}
	if (ch == '\0')
		return (p + i + 1);
	return (0);
}

void	getting_util_envs(char **envp, char **dst, int *i)
{
	char	buff[FILENAME_MAX];

	if (!find_oldpwd(envp))
		dst[(*i)++] = ft_strdup("OLDPWD");
	if (!find_pwd(envp))
	{
		getcwd(buff, sizeof(buff));
		dst[(*i)++] = ft_strjoin("PWD=", buff);
	}
	if (!find_shlvl(envp))
		dst[(*i)++] = ft_strdup("SHLVL=1");
}

char	**add_basic_envs(char **envp)
{
	char	**dst;
	int		i;
	int		x;

	i = 0;
	x = find_initial_envs(envp);
	dst = malloc(sizeof(char *) * (ft_matrixlen(envp) + x));
	while (envp[i])
	{
		dst[i] = ft_strdup(envp[i]);
		dst[++i] = NULL;
	}
	getting_util_envs(envp, dst, &i);
	dst[i] = NULL;
	return (dst);
}

void	take_envs(char	**envp, t_env *env)
{
	int		i;

	i = 0;
	if (!*envp)
		env->envp = add_basic_envs(envp);
	else
	{
		env->envp = ft_matrixdup(envp);
		change_shlvl(env);
	}
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			add_slash_to_path(env, envp[i]);
		if (ft_strncmp("USER=", envp[i], 5) == 0)
			env->user = ft_strchr2(envp[i], '=');
		if (ft_strncmp("HOME=", envp[i], 5) == 0)
			env->home = ft_strchr2(envp[i], '=');
		if (ft_strncmp("PWD=", envp[i], 4) == 0)
			env->pwd = ft_strchr2(envp[i], '=');
		if (ft_strncmp("OLDPWD", envp[i], 7) == 0)
			env->oldpwd = NULL;
		i++;
	}
}
