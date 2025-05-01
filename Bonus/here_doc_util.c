/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:35:43 by kahmada           #+#    #+#             */
/*   Updated: 2024/05/31 00:04:04 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	handle_child(const char *limiter, int tmp_fd)
{
	char	*line;
	size_t	len;

	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		len = ft_strlen(line);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			exit(0);
		}
		write(tmp_fd, line, len);
		free(line);
	}
	exit(0);
}

int	handle_here_doc(const char *limiter)
{
	int		tmp_fd;
	pid_t	pid;

	tmp_fd = open("tempfile.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmp_fd == -1)
		error();
	pid = fork();
	if (pid < 0)
		error();
	if (pid == 0)
		handle_child(limiter, tmp_fd);
	close(tmp_fd);
	tmp_fd = open("tempfile.txt", O_RDWR, 0644);
	if (tmp_fd == -1)
		error();
	unlink("tempfile.txt");
	wait(NULL);
	return (tmp_fd);
}

static void	child_proc(char **cmd_args, int pi_fd[], char *envp[], int fd_in)
{
	char	*full_cmd;

	close(pi_fd[0]);
	if (dup2(fd_in, 0) == -1)
		error();
	close(fd_in);
	if (dup2(pi_fd[1], 1) == -1)
		error();
	close(pi_fd[1]);
	full_cmd = find_commande(cmd_args[0], envp);
	if (!full_cmd)
		error();
	if (execve(full_cmd, cmd_args, envp) == -1)
		error();
	exit (0);
}

void	child_proc2(char **cmd_arg, int pi_fd[], char *envp[], const char *outf)
{
	int		outfile_fd;
	char	*full_cmd;

	close(pi_fd[1]);
	outfile_fd = open(outf, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error();
	if (dup2(outfile_fd, 1) == -1)
		error();
	close(outfile_fd);
	if (dup2(pi_fd[0], 0) == -1)
		error();
	close(pi_fd[0]);
	full_cmd = find_commande(cmd_arg[0], envp);
	if (!full_cmd)
		error();
	if (execve(full_cmd, cmd_arg, envp) == -1)
		error();
	exit (0);
}

void	setup_fork_procs(t_list *proc1_info, t_list *proc2_info, int pipefd[])
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		error();
	pid1 = fork();
	if (pid1 < 0)
		error();
	else if (pid1 == 0)
		child_proc(proc1_info->cmd_args, pipefd,
			proc1_info->envp, proc1_info->fd_in);
	pid2 = fork();
	if (pid2 < 0)
		error();
	else if (pid2 == 0)
		child_proc2(proc2_info->cmd_args, pipefd,
			proc2_info->envp, proc2_info->outfile);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	cleanup_2darray(proc1_info->cmd_args, proc2_info->cmd_args);
}
