/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:56:26 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 14:34:46 by ayoakouh         ###   ########.fr       */
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

void	wait_for_children(t_cmd *cmd, pid_t child_pid)
{
	int	status;
	int	sig;

	status = 0;
	sig = 0;
	waitpid(child_pid, &status, 0);
	cmd->data.exit_status = get_or_set(SET, WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			cmd->data.exit_status = get_or_set(SET, 128 + sig);
		}
		else if (sig == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			cmd->data.exit_status = get_or_set(SET, 128 + sig);
		}
		else
			cmd->data.exit_status = get_or_set(SET, 0);
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

void	ft_print_error(t_cmd *cmd, int flag)
{
	if (errno == 20)
	{
		ft_putstr_fd("minishell: ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		ft_putstr_fd(": Not a directory\n", 2);
		exit(1);
	}
	if (errno == 2 && ft_strchr(cmd->args[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		ft_putstr_fd(": No such file or directory\n", 2);
		cmd->data.exit_status = get_or_set(SET, 127);
		exit(127);
	}
	else if (errno == 13)
	{
		ft_putstr_fd("minishell: ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		cmd->data.exit_status = get_or_set(SET, 126);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	if (errno == 21)
	{
		ft_putstr_fd("minishell: ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		cmd->data.exit_status = get_or_set(SET, 126);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if(errno == 2 && flag == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		ft_putstr_fd(": No such file or directory\n", 2);
		cmd->data.exit_status = get_or_set(SET, 127);
		exit(127);
	}
}

	// else if (chdir(cmd->args[0]) == -1)
	// {
	// 	if (errno == 20)
	// 	{
	// 		write(2, "minishell: ", 11);
	// 		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	// 		write(2, ": Not a directory\n", 18);
	// 		cmd->data.exit_status = get_or_set(SET, 126);
	// 		exit(126);
	// 	}
	// }