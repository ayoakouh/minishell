/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 21:21:52 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 14:45:14 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_absolute_path(t_cmd *cmd, char **help, int flag)
{
	if (flag == 1)
	{
		fork_to_child(cmd, help);
	}
	else
	{
		check_directory(cmd);
		if (access(cmd->args[0], X_OK) == 0)
		{
			execve(cmd->args[0], cmd->args, help);
			cmd->data.exit_status = get_or_set(SET, 0);
		}
		else
			ft_print_error(cmd, 0);
	}
}

void	check_access(t_cmd *cmd, char *helper, char **split_path,
	char **env_array)
{
	if ((access(helper, X_OK) != -1))
	{
		puts("000");
		if (execve(helper, cmd->args, env_array) == -1)
		{
			if (errno == 20 || (errno == 2 && ft_strchr(cmd->args[0], '/')))
			{
				printf("....%d\n", errno);
				ft_free_split(split_path);
				ft_print_error(cmd, 0);
			}
		}
	}
	ft_print_error(cmd, 0);
}

void	ft_execute_path_command(t_cmd *cmd, char **env_array, char **split_path)
{
	char	*tmp;
	char	*helper;
	int		i;

	i = 0;
	if (access(cmd->args[0], X_OK) != -1 && ft_strchr(cmd->args[0], '/'))
		ft_print_error(cmd, 0);
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		helper = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (!helper)
		{
			i++ ;
			continue ;
		}
		check_access(cmd, helper, split_path, env_array);
		free(helper);
		i++;
	}
	ft_free_split(split_path);
	write_error(cmd);
}

void	handle_child(t_cmd *cmd, t_env *env_list, char *env[])
{
	char	*path;
	char	**split_path;

	restart_setting_term();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = check_path(&env_list);
	if (!path || !*path)
	{
		if_path_null(&cmd, env);
		return ;
	}
	else
	{
		split_path = ft_split(path, ':');
		if (!split_path)
			return ;
		check_is_derctory(cmd, path);
		ft_execute_path_command(cmd, env, split_path);
		ft_free_split(split_path);
	}
}

void	ft_excute_commands(t_cmd *cmd, t_env **env_list, int flag)
{
	char	**env_doble;
	pid_t	child_pid;

	signal(SIGINT, SIG_IGN);
	if (!cmd->args || !cmd->args[0])
		return ;
	env_doble = convert_env_list(env_list);
	if (ft_strchr(cmd->args[0], '/'))
	{
		handle_absolute_path(cmd, env_doble, flag);
		return ;
	}
	if (flag == 1)
	{
		child_pid = fork();
		if (child_pid == 0)
			handle_child(cmd, *env_list, env_doble);
		else if (child_pid > 0)
		{
			wait_for_children(cmd, child_pid);
		}
	}
	else
		handle_child(cmd, *env_list, env_doble);
	free_split_str(env_doble);
}
//this for excute_path-command;;;;
		// if (!(access(helper, X_OK) == -1))
		// {
		// 	if (execve(helper, cmd->args, env_array) == -1)
		// 	{
		// 		ft_free_split(split_path);
		// 		write_error(cmd);
		// 	}
		// }		
// void wait_for_children(t_cmd *cmd, pid_t child_pid)
// {
// 	int status;

// 	status = 0;
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// 	waitpid(child_pid, &status, 0);
// 	cmd->data.exit_status = WEXITSTATUS(status);
// 		if (WIFSIGNALED(status))
// 		{
// 			int sig = WTERMSIG(status);
// 			if (sig == SIGQUIT)
// 			{
// 				ft_putstr_fd("Quit: 3\n", 1);
// 				cmd->data.exit_status = get_or_set(SET, 128 + sig);
// 			}
// 			else if (sig == SIGINT)
// 			{
// 				ft_putstr_fd("\n", 1);
// 				cmd->data.exit_status = get_or_set(SET, 128 + sig);
// 			}
// 			else
// 				cmd->data.exit_status = get_or_set(SET, 0);
// 		}
// }

// int	check(t_cmd *cmd)
// {
// 	struct stat	err;

// 	if (!stat(cmd->args[0], &err) && S_ISDIR(err.st_mode))
// 	{
// 		if (!ft_strchr(cmd->args[0], '/'))
// 		{
// 			write(2, "minishell: ", 11);
// 			write(2, cmd->args[0], ft_strlen(cmd->args[0]));
// 			write(2, ": is a directory\n", 17);
// 			cmd->data.exit_status = get_or_set(SET, 126);
// 			exit (126);
// 		}
// 		return (1);
// 	}
// 	return (0);
// }