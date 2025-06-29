/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:13:31 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 15:11:33 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->pipe_out)
		{
			if (tmp->fd_pipe[0] != -1)
			{
				close(tmp->fd_pipe[0]);
				tmp->fd_pipe[0] = -1;
			}
			if (tmp->fd_pipe[1] != -1)
			{
				close(tmp->fd_pipe[1]);
				tmp->fd_pipe[1] = -1;
			}
		}
		tmp = tmp->next;
	}
}

void	pipe_all(t_cmd *head)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = head;
	tmp = head;
	while (cmd)
	{
		if (cmd->pipe_out)
		{
			if (pipe(cmd->fd_pipe) == -1)
			{
				close_all_pipes(tmp);
				close_all(tmp);
				kill_and_wait_all(tmp);
				waitpid(-1, NULL, 0);
				perror("pipe");
				return ;
			}
		}
		cmd = cmd->next;
	}
}

void	check_signals(int status, t_cmd *head)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 1);
		else if (WTERMSIG(status) == SIGINT)
		{
			close_all(head);
			ft_putstr_fd("\n", 1);
		}
	}
}

void	dup_pipe(t_cmd *cmd, t_cmd *prev)
{
	if (prev && prev->pipe_out)
	{
		dup2(prev->fd_pipe[0], STDIN_FILENO);
		close(prev->fd_pipe[0]);
		prev->fd_pipe[0] = -1;
	}
	if (cmd->pipe_out)
	{
		dup2(cmd->fd_pipe[1], STDOUT_FILENO);
		close(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
}
