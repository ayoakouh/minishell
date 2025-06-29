/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:36:49 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/26 17:39:41 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_prev_pipe(t_cmd *prev)
{
	if (prev && prev->pipe_out)
	{
		if (prev->fd_pipe[0] != -1)
		{
			close(prev->fd_pipe[0]);
			prev->fd_pipe[0] = -1;
		}
		if (prev->fd_pipe[1] != -1)
		{
			close(prev->fd_pipe[1]);
			prev->fd_pipe[1] = -1;
		}
	}
}

void	close_child_pipes(t_cmd *head)
{
	t_cmd	*tmp;

	tmp = head;
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

void	handle_parent_cleanup(t_cmd *cmd, t_cmd *prev, pid_t pid)
{
	cmd->pid = pid;
	if (prev && prev->pipe_out)
	{
		if (prev->fd_pipe[0] != -1)
			close(prev->fd_pipe[0]);
		prev->fd_pipe[0] = -1;
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

char	*get_value(char *str)
{
	int				i;
	int				tmp;
	unsigned int	len;
	char			*helper;

	i = 0;
	len = 0;
	helper = NULL;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '=')
		i++;
	tmp = i;
	while (str[i])
	{
		len++;
		i++;
	}
	helper = ft_substr(str, tmp, len);
	if (!helper)
		return (NULL);
	return (helper);
}
