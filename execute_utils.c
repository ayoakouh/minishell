/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:17:31 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 14:44:49 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(t_env **list)
{
	t_env	*tmp;

	if (!list || !*list)
		return (NULL);
	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "PATH"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	fork_to_child(t_cmd *cmd, char **help)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		check_directory(cmd);
		if (access(cmd->args[0], X_OK) == 0)
		{
			execve(cmd->args[0], cmd->args, help);
			cmd->data.exit_status = get_or_set(SET, 0);
			exit(0);
		}
		else
			ft_print_error(cmd, 0);
	}
	else if (child_pid < 0)
	{
		perror("fork");
		exit(0);
	}
	else
		wait_for_children(cmd, child_pid);
}

void	write_error(t_cmd *cmd)
{
	write(2, "11minishell: ", 13);
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, ": command not found\n", 20);
	cmd->data.exit_status = get_or_set(SET, 127);
	exit(127);
}

void	check_is_derctory(t_cmd *cmd, char *path)
{
	struct stat	err;

	if (!stat(cmd->args[0], &err) && (S_ISDIR(err.st_mode)))
	{
		if ((cmd && path && !ft_strcmp(cmd->args[0], ".."))
			|| (path && !ft_strchr(cmd->args[0], '/')))
		{
			write_error(cmd);
		}
	}
}
