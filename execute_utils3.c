/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:12 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 21:19:12 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_and_wait_all(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp != NULL)
	{
		if (tmp->pid > 0)
		{
			kill(tmp->pid, SIGKILL);
			waitpid(tmp->pid, NULL, 0);
			tmp->pid = -1;
		}
		tmp = tmp->next;
	}
	cmd->data.exit_status = get_or_set(SET, 1);
}

void	wait_last_pid(pid_t last_pid, t_cmd *head)
{
	int	status;
	int	last_status;
	int	pid;

	pid = 0;
	status = 0;
	last_status = 0;
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
			{
				last_status = WEXITSTATUS(status);
				head->data.exit_status = get_or_set(SET, last_status);
			}
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		head->data.exit_status = get_or_set(SET, last_status);
		pid = waitpid(-1, &status, 0);
	}
	check_signals(status, head);
	get_or_set(SET, head->data.exit_status);
}

void	close_all(t_cmd *cmd)
{
	t_redir	*red;

	if (!cmd || !cmd->redirs)
		return ;
	while (cmd)
	{
		red = cmd->redirs;
		while (red)
		{
			if (red->fd[0] > 2)
			{
				close(red->fd[0]);
				red->fd[0] = -1;
			}
			if (red->fd[1] > 2)
			{
				close(red->fd[1]);
				red->fd[1] = -1;
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
}

void	sig_default_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

char	**convert_env_list(t_env **list)
{
	t_env	*tmp;
	char	**helper;
	char	*str;
	char	*temp;
	int		i;

	i = 0;
	str = NULL;
	temp = NULL;
	tmp = *list;
	helper = malloc(sizeof(char *) * (ft_list_size(*list) + 1));
	while (tmp)
	{
		str = ft_strjoin(tmp->key, "=");
		temp = ft_strjoin(str, tmp->value);
		free(str);
		helper[i++] = temp;
		tmp = tmp->next;
	}
	helper[i] = NULL;
	return (helper);
}
