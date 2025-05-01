/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:02:27 by kahmada           #+#    #+#             */
/*   Updated: 2024/06/01 08:23:10 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	split_and_check(char *arg, char ***cmd_args)
{
	*cmd_args = ft_split(arg);
	if (!*cmd_args)
		error();
}

int	is_whitespace_or_tab(char *str)
{
	char	c;

	while (*str)
	{
		c = *str;
		if (!(c == 32 || (c >= 9 && c <= 13)))
			return (0);
		str++;
	}
	return (1);
}

int	check_arguments(char *argv[], int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (is_whitespace_or_tab(argv[i]))
			error();
		i++;
	}
	return (1);
}

void	cleanup_2darray(char **cmd_args1, char **cmd_args2)
{
	int	i;

	i = 0;
	while (cmd_args1 && cmd_args1[i])
	{
		free(cmd_args1[i]);
		i++;
	}
	if (cmd_args1)
		free(cmd_args1);
	i = 0;
	while (cmd_args2 && cmd_args2[i])
	{
		free(cmd_args2[i]);
		i++;
	}
	if (cmd_args2)
		free(cmd_args2);
}

void	error(void)
{
	write(2, "ERROR\n", 6);
	exit(1);
}
