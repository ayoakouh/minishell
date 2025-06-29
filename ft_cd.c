/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:05:15 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/29 10:03:40 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dot(char **str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_strcmp(str[i], ".."))
			return (1);
		i++;
	}
	return (0);
}

int	ft_chdir(char *new_cwd, char *str)
{
	char	**split_string;

	split_string = NULL;
	if (home_not_set(new_cwd) == 1)
		return (1);
	if (new_cwd != NULL && chdir(new_cwd) == -1)
	{
		split_string = ft_split(new_cwd, '/');
		if (check_dot(split_string) == 1)
		{
			if (check_string(split_string, str) == 1)
				return (1);
			ft_free_split(split_string);
		}
		else
		{
			ft_free_split(split_string);
			_print_error(NULL, str, 0);
			return (1);
		}
	}
	return (0);
}

static char	*hold_value_of_pwd(t_env **list, char **str, t_cmd *cmd)
{
	char	*cwd;
	char	*new_pw;

	new_pw = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cmd->data.new_pwd = get_set(NULL, 1);
		if (cmd->data.new_pwd)
			new_pw = check_pwd(list, str[1], cmd->data.new_pwd);
		cmd->data.new_pwd = get_set(new_pw, 0);
		free(new_pw);
		return (cmd->data.new_pwd);
	}
	cmd->data.new_pwd = get_set(cwd, 0);
	free(cwd);
	return (cmd->data.new_pwd);
}

int	ft_cd(char **str, t_env **list, t_cmd *cmd)
{
	char	*new_cwd;
	char	*value;
	char	*final_pwd;

	value = NULL;
	final_pwd = NULL;
	new_cwd = get_path(str[1], list);
	if (check_home(list, str[1]) == 0)
		return (0);
	value = get_value_env("PWD", list);
	if (ft_chdir(new_cwd, str[1]) == 1)
		return (1);
	if (value)
		set_value_env(list, "OLDPWD", value);
	final_pwd = hold_value_of_pwd(list, str, cmd);
	set_value_env(list, "PWD", final_pwd);
	return (0);
}
