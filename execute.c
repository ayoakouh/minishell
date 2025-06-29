/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:46:03 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 15:42:29 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_and_check_heredoc(t_cmd **command, t_env *env_list)
{
	(*command)->fd[0] = dup(0);
	(*command)->fd[1] = dup(1);
	check_here_doc(*command, env_list);
	if ((*command)->flag == 1)
	{
		cleanup_all_heredocs(*command);
		restory_window(*command);
		return (1);
	}
	return (0);
}

void	check_line(t_cmd **command, t_env **env_list)
{
	t_cmd	*cmd;

	if (prepare_and_check_heredoc(command, *env_list))
		return ;
	cmd = *command;
	if (cmd->pipe_out)
	{
		ft_excute_mult_pipe(cmd, *env_list);
		cleanup_all_heredocs(cmd);
		get_or_set(SET, cmd->data.exit_status);
		restory_window(cmd);
		return ;
	}
	if (excute_redrction(command) == -1)
	{
		restory_window(cmd);
		return ;
	}
	execute_single_command(*command, env_list, 1);
	restory_window(cmd);
}

void	wait_parent_children(t_cmd *cmd, pid_t child_pid)
{
	int	status;
	int	sig;

	status = 0;
	sig = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(child_pid, &status, 0);
	cmd->data.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 1);
		else if (sig == SIGINT)
		{
			cmd->flag = 1;
			cmd->data.exit_status = get_or_set(SET, 1);
		}
		else
		{
			cmd->data.exit_status = get_or_set(SET, 0);
		}
	}
}

int	excute_redrction(t_cmd **cmd)
{
	if ((*cmd)->redirs)
	{
		if ((*cmd)->redirs->fd[0] == -1)
		{
			(*cmd)->data.exit_status = get_or_set(SET, 1);
			restory_window((*cmd));
			return (-1);
		}
		ft_redircte((*cmd)->redirs);
	}
	return (0);
}

void	excute_builting(t_cmd **command, t_env **env_list)
{
	t_cmd	*cmd;
	int		status;

	cmd = *command;
	status = 0;
	if (strncmp("export", cmd->args[0], 6) == 0)
		status = ft_export(cmd->args, env_list);
	else if (strncmp("env", cmd->args[0], 3) == 0)
		status = ft_env(*command, *env_list);
	else if (strncmp("exit", cmd->args[0], 4) == 0)
		status = ft_exit(cmd->args, cmd->data);
	else if (strncmp("unset", cmd->args[0], 5) == 0)
		status = ft_unset(env_list, cmd->args + 1);
	else if (strncmp("echo", cmd->args[0], 4) == 0)
		status = echo(cmd->args);
	else if (strncmp("pwd", cmd->args[0], 3) == 0)
		status = pwd(cmd);
	else if (strncmp("cd", cmd->args[0], 2) == 0)
		status = ft_cd(cmd->args, env_list, cmd);
	cmd->data.exit_status = get_or_set(SET, status);
}
