/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 11:37:50 by rcabezas          #+#    #+#             */
/*   Updated: 2021/11/25 10:38:29 by rcabezas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execute_pwd(void)
{
	char	buf[FILENAME_MAX];

	printf("%s\n", getcwd(buf, sizeof(buf)));
	return (0);
}
