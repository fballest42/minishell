/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environments_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:02:44 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/10 12:03:31 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	assign_path(t_env *env, char *str)
{
	char	*aux;

	aux = ft_strchr2(str, '=');
	if (!env->paths)
		add_slash_to_path(env, str);
}

int	check_env(char *env, char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (!ft_strncmp(env, list[i], ft_strlen(env)))
			return (1);
		i++;
	}
	return (0);
}

char	**order_envs(char **envs)
{
	char	**ordered;
	char	*tmp;
	int		i;
	int		j;

	ordered = ft_matrixdup(envs);
	i = 0;
	while (i < ft_matrixlen(envs))
	{
		j = 1;
		while (ordered[j])
		{
			if (ft_strcmp(ordered[j - 1], ordered[j]) > 0)
			{
				tmp = ordered[j - 1];
				ordered[j - 1] = ordered[j];
				ordered[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (ordered);
}
