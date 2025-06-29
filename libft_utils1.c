/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:56:26 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/29 10:04:06 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_skip_export(char *str, t_env **lst, char *key, char *value)
{
	if (ft_strchr(str, '=') == NULL && ft_check(*lst, key) == 1)
	{
		free(value);
		free(key);
		return (1);
	}
	return (0);
}

void	check_directory(t_cmd *cmd)
{
	struct stat	err;

	if (!stat(cmd->args[0], &err))
	{
		if (S_ISDIR(err.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
			write(2, ": is a directory\n", 17);
			cmd->data.exit_status = get_or_set(SET, 126);
			exit(126);
		}
	}
}

void	if_path_null(t_cmd **cmd, char *env[])
{
	int	fd;

	fd = 0;
	if (ft_strcmp((*cmd)->args[0], "..") == 0)
		_print_error(cmd, NULL, 1);
	if (access((*cmd)->args[0], X_OK) != -1)
	{
		fd = open((*cmd)->args[0], O_DIRECTORY);
		if (fd != -1)
		{
			_print_error(cmd, NULL, 1);
		}
		execve((*cmd)->args[0], (*cmd)->args, env);
		exit(0);
	}
	else
	{
		ft_print_error(*cmd, 1);
	}
}

void	print_hp(t_cmd *cmd, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	if (flag == 0)
	{
		ft_putstr_fd(": Not a directory\n", 2);
		cmd->data.exit_status = get_or_set(SET, 126);
		exit(126);
	}
	if (flag == 1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		cmd->data.exit_status = get_or_set(SET, 127);
		exit(127);
	}
	if (flag == 2)
	{
		cmd->data.exit_status = get_or_set(SET, 126);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (flag == 3)
	{
		cmd->data.exit_status = get_or_set(SET, 126);
		ft_putstr_fd(": Is a directory\n", 2);
	}
}

void	ft_print_error(t_cmd *cmd, int flag)
{
	if (errno == 20)
	{
		print_hp(cmd, 0);
		exit(126);
	}
	if ((errno == 2 && ft_strchr(cmd->args[0], '/'))
		|| (errno == 2 && flag == 1))
	{
		print_hp(cmd, 1);
		exit(127);
	}
	else if (errno == 13)
	{
		print_hp(cmd, 2);
		exit(126);
	}
	if (errno == 21)
	{
		print_hp(cmd, 3);
		exit(126);
	}
}
