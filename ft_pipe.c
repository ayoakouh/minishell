/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:27:19 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 15:04:59 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_process(t_cmd *cmd, t_cmd *prev, t_env *env_list,
	t_cmd *head)
{
	sig_default_child();
	dup_pipe(cmd, prev);
	if (cmd->redirs && !isatty(cmd->redirs->fd[0]))
	{
		if (ft_redircte(cmd->redirs) == -1)
		{
			close_child_pipes(head);
			close_all(head);
			cmd->data.exit_status = get_or_set(SET, 1);
			exit(1);
		}
	}
	close_child_pipes(head);
	execute_single_command(cmd, &env_list, 0);
	exit(cmd->data.exit_status);
}

static int	fork_exec(t_cmd *cmd, t_cmd *prev, t_env *env_list, t_cmd *head)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close_all_pipes(head);
		close_all(head);
		kill_and_wait_all(head);
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		handle_child_process(cmd, prev, env_list, head);
	else
		handle_parent_cleanup(cmd, prev, pid);
	return (0);
}

static int	ft_cleanup_after_cmd(t_cmd *cmd, t_cmd *prev, t_cmd *head)
{
	if (cmd->pipe_out)
	{
		close(cmd->fd_pipe[1]);
		cmd->fd_pipe[1] = -1;
	}
	close_prev_pipe(prev);
	if (cmd->redirs && cmd->redirs->fd[0])
		close(cmd->redirs->fd[0]);
	if (cmd->flag == 1)
	{
		close_all(head);
		exit(130);
	}
	return (0);
}

static void	ft_execute_pipes_loop(t_cmd *head, t_env *env, pid_t *last_pid)
{
	t_cmd	*cmd;
	t_cmd	*prev;

	cmd = head;
	prev = NULL;
	while (cmd)
	{
		if (fork_exec(cmd, prev, env, head) == -1)
		{
			close_all_pipes(head);
			close_all(head);
			kill_and_wait_all(head);
			return ;
		}
		if (!cmd->next)
			*last_pid = cmd->pid;
		ft_cleanup_after_cmd(cmd, prev, head);
		prev = cmd;
		cmd = cmd->next;
	}
	close_prev_pipe(prev);
}

void	ft_excute_mult_pipe(t_cmd *cmd, t_env *env)
{
	t_cmd	*head;
	pid_t	last_pid;

	head = cmd;
	last_pid = 0;
	signal(SIGINT, SIG_IGN);
	pipe_all(cmd);
	ft_execute_pipes_loop(head, env, &last_pid);
	close_all(head);
	wait_last_pid(last_pid, head);
}
	// if (!cmd->redirs || cmd->redirs->fd[0] != -1)

// static int fork_exec(t_cmd *cmd, t_cmd *prev, t_env *env_list, t_cmd *head)
// {
// 	int i;

// 	i = 0;
// 	pid_t pid = fork();
// 	if (pid < 0)
// 	{
//         handle_errors(&head);
// 		return (-1);
// 	}
// 	if (pid == 0)
// 	{
// 		sig_default_child();
// 		dup_pipe(cmd, prev);
// 		if (cmd->redirs && !isatty(cmd->redirs->fd[0]))
// 		{
// 			if(ft_redircte(cmd->redirs) == -1)
// 			{
// 				cmd->data.exit_status = get_or_set(SET , 1);
// 				exit(1);
// 			}
// 		}
// 		close_child_pipes(head);
// 		if (!cmd->redirs || cmd->redirs->fd[0] != -1)
// 			execute_single_command(cmd, &env_list, 0);
// 		exit(cmd->data.exit_status);
// 	}
// 	if (pid)
// 		cmd->pid = pid;
// 	if (prev && prev->pipe_out)
//     {
// 		if(prev->fd_pipe[0] != -1)
//         	close(prev->fd_pipe[0]);
// 		prev->fd_pipe[0] = -1;
//     }
// 	return (0);
// }