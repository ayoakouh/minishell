/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:25:09 by kahmada           #+#    #+#             */
/*   Updated: 2024/05/31 06:59:36 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command(int in_fd, int out_fd, char **cmd_args, char *envp[])
{
	char	*full_cmd;

	full_cmd = find_commande(cmd_args[0], envp);
	if (!full_cmd)
		error();
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (out_fd != 1)
	{
		dup2(out_fd, 1);
		close(out_fd);
	}
	if (execve(full_cmd, cmd_args, envp) == -1)
		error();
}

void	fork_and_execute_command(int in_fd, int out_fd, char *cmd, char *envp[])
{
	char	**cmd_args;
	char	**arg;
	pid_t	pid;

	cmd_args = ft_split(cmd);
	if (!cmd_args)
		error();
	pid = fork();
	if (pid < 0)
		error();
	else if (pid == 0)
		execute_command(in_fd, out_fd, cmd_args, envp);
	arg = cmd_args;
	while (*arg)
	{
		free(*arg);
		arg++;
	}
	free(cmd_args);
}

void	setuppipesandexecute(int inf_fd, int out_fd, char *av[], char *envp[])
{
	int	argc;
	int	num_pipes;
	int	prev_fd;
	int	i;
	int	pipefd[2];

	argc = 0;
	while (av[argc] != NULL)
		argc++;
	num_pipes = argc - 4;
	prev_fd = inf_fd;
	i = 0;
	while (i < num_pipes)
	{
		pipe(pipefd);
		fork_and_execute_command(prev_fd, pipefd[1], av[i + 2], envp);
		close(pipefd[1]);
		prev_fd = pipefd[0];
		i++;
	}
	fork_and_execute_command(prev_fd, out_fd, av[num_pipes + 2], envp);
}

static void	wait_for_children(int num_children)
{
	int	i;

	i = 0;
	while (i < num_children)
	{
		wait(NULL);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	infile_fd;
	int	outfile_fd;

	if (argc < 5)
		error();
	if (!check_arguments(argv, argc))
		error();
	if (argc == 6 && (ft_strcmp(argv[1], "here_doc") == 1))
		handle_here_doc_and_execute(argv, 0, envp);
	else
	{
		outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd == -1)
			error();
		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd == -1)
			error();
		setuppipesandexecute(infile_fd, outfile_fd, argv, envp);
		close(infile_fd);
		close(outfile_fd);
		wait_for_children(argc - 4);
	}
	return (0);
}
