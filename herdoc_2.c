/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:42:49 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/29 10:13:59 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_hp_0(t_redir *tmp_redir, t_env *env)
{
	t_heredoc_var	data;

	data.env = env;
	data.exit_status = 0;
	data.orig_delimiter = tmp_redir->orig_token;
	data.fd = tmp_redir->fd[0];
	signal(SIGINT, SIG_DFL);
	heredoc(tmp_redir->file, &data);
	exit(0);
}

void	heredoc_hp_1(pid_t	pid, t_cmd *cmd, t_redir *tmp_redir)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		cmd->data.exit_status = get_or_set(SET, 1);
		close_all(cmd);
		cmd->flag = 1;
		return ;
	}
	cmd->flag = 0;
}

void	heredoc_hp_2(t_redir *tmp_redir, t_cmd *cmd)
{
	perror("fork");
	close_all(cmd);
	cmd->flag = 1;
	return ;
}

void	heredoc_main_helper(pid_t pid, t_cmd *cmd, t_redir *tmp_redir)
{
	if (pid > 0)
		heredoc_hp_1(pid, cmd, tmp_redir);
	else
		heredoc_hp_2(tmp_redir, cmd);
}

void	(t_cmd *cmd, t_env *env)
{
	t_cmd	*tmp;
	t_redir	*tmp_redir;
	pid_t	pid;

	tmp = cmd;
	max_heredoc(cmd);
	while (tmp)
	{
		tmp_redir = tmp->redirs;
		while (tmp_redir)
		{
			if (tmp_redir->type == 3)
			{
				pid = fork();
				if (pid == 0)
					heredoc_hp_0(tmp_redir, env);
				else
					heredoc_main_helper(pid, cmd, tmp_redir);
				if (cmd->flag)
					return ;
			}
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
}
