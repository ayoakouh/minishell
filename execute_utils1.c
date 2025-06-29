/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:58:06 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 15:14:08 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_single_command(t_cmd *cmd, t_env **list_env, int flag)
{
	if (!is_builtin(cmd->args))
	{
		excute_builting(&cmd, list_env);
		get_or_set(SET, cmd->data.exit_status);
	}
	else
	{
		ft_excute_commands(cmd, list_env, flag);
		get_or_set(SET, cmd->data.exit_status);
	}
}

void	check_set(t_env **env)
{
	t_env	*tmp;
	int		path;
	int		oldpwd;
	int		pwd;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			path = 1;
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			oldpwd = 1;
		else if (ft_strcmp(tmp->key, "PWD") == 0)
			pwd = 1;
		tmp = tmp->next;
	}
	if (path != 1)
		ft_lstadd_back_env(env, creat_new_env(ft_strdup("PATH"),
				ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
	if (oldpwd != 1)
		ft_lstadd_back_env(env, creat_new_env(ft_strdup("OLDPWD"), NULL));
	if (pwd != 1)
		ft_lstadd_back_env(env, creat_new_env(ft_strdup("PWD"),
				getcwd(NULL, 0)));
}

void	restory_window(t_cmd *cmd)
{
	dup2(cmd->fd[0], 0);
	dup2(cmd->fd[1], 1);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}

void	closed(t_redir *red)
{
	if (red->type == 3)
	{
		if (red->fd[0] > 0)
		{
			close(red->fd[0]);
			red->fd[0] = -1;
		}
		if (red->fd[1] > 0)
		{
			close(red->fd[1]);
			red->fd[1] = -1;
		}
	}
}

void	cleanup_all_heredocs(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*tmp_redir;

	tmp = cmd;
	while (tmp)
	{
		tmp_redir = tmp->redirs;
		while (tmp_redir)
		{
			closed(tmp_redir);
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
}
