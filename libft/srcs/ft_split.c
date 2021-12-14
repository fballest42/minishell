/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:59:10 by rcabezas          #+#    #+#             */
/*   Updated: 2021/12/06 21:57:16 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	destroy(char **a)
{
	free(a);
	a = NULL;
	exit (EXIT_SUCCESS);
}

static int	ft_countwords(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static char	*ft_word(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s, char c)
{
	char	**a;
	int		i;

	if (s == NULL)
		return (NULL);
	a = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!a)
		destroy(a);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			a[i] = ft_word(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	a[i] = NULL;
	return (a);
}
