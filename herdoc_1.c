/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:40:57 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/29 10:03:10 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_to_file(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
		ft_putchar_fd(0, fd);
	else
	{
		while (str && str[i])
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	close(fd);
	free(str);
}

int	max_heredoc_checker(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*tp;
	int		count;

	count = 0;
	tp = NULL;
	tmp = cmd;
	while (tmp)
	{
		tp = tmp->redirs;
		while (tp)
		{
			if (tp->type == 3)
				count++;
			tp = tp->next;
		}
		tmp = tmp->next;
	}
	if (count > 16)
	{
		write(2, "minishell:  maximum here-document count exceeded\n", 50);
		exit(2);
	}
	return (0);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	exit(130);
}

void	max_heredoc(t_cmd *cmd)
{
	max_heredoc_checker(cmd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
