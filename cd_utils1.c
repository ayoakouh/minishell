/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:44:02 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 16:39:32 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_string(char **split_string, char *str)
{
	char	*helper;
	char	*tmp;

	helper = NULL;
	tmp = NULL;
	if (get_set(NULL, 0) != NULL)
	{
		helper = ft_strdup(get_set(NULL, 0));
		tmp = setup_string(helper);
		if (chdir(tmp) == -1)
		{
			_print_error(NULL, str, 0);
			free(tmp);
			ft_free_split(split_string);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int	directory_change(char *new_cwd, char *target)
{
	return (ft_chdir(new_cwd, target));
}

int	is_builtin(char **args)
{
	if (!args || !*args)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(args[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(args[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(args[0], "export") == 0)
		return (0);
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (0);
	else if (ft_strcmp(args[0], "env") == 0)
		return (0);
	else if (ft_strcmp(args[0], "exit") == 0)
		return (0);
	else
		return (1);
}
