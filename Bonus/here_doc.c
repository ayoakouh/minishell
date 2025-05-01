/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:36:29 by kahmada           #+#    #+#             */
/*   Updated: 2024/06/01 08:23:42 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc_and_execute(char *argv[], int fd_in, char *envp[])
{
	char	**cmd1_args;
	char	**cmd2_args;
	t_list	proc1_info;
	t_list	proc2_info;
	int		pipefd[2];

	fd_in = handle_here_doc(argv[2]);
	split_and_check(argv[3], &cmd1_args);
	split_and_check(argv[4], &cmd2_args);
	proc1_info.cmd_args = cmd1_args;
	proc1_info.fd_in = fd_in;
	proc1_info.infile = "temple.txt";
	proc1_info.outfile = NULL;
	proc1_info.envp = envp;
	proc2_info.cmd_args = cmd2_args;
	proc2_info.fd_in = 0;
	proc2_info.infile = NULL;
	proc2_info.outfile = argv[5];
	proc2_info.envp = envp;
	setup_fork_procs(&proc1_info, &proc2_info, pipefd);
}
