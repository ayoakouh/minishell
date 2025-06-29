/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:30:57 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 20:24:42 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_heredoc_line(char *heredoc, char *new_line)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(new_line, "\n");
	if (!tmp1)
		return (NULL);
	if (heredoc == NULL)
		return (tmp1);
	tmp2 = ft_strjoin(heredoc, tmp1);
	free(heredoc);
	free(tmp1);
	return (tmp2);
}

char	*process_single_line(char *line, t_heredoc_var *data)
{
	char	*expanded_line;

	expanded_line = process_heredoc_epxand(line, data->env,
			data->orig_delimiter);
	free(line);
	return (expanded_line);
}

char	*read_heredoc_lines(char *delimiter, t_heredoc_var *data)
{
	char	*line;
	char	*heredoc;
	char	*expanded_line;

	heredoc = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = process_single_line(line, data);
		heredoc = join_heredoc_line(heredoc, expanded_line);
		free(expanded_line);
		if (!heredoc)
			break ;
	}
	return (heredoc);
}

void	heredoc(char *delimiter, t_heredoc_var *data)
{
	char	*processed_delimiter;
	char	*heredoc_content;

	processed_delimiter = heredoc_delemter(ft_strdup(data->orig_delimiter));
	if (!processed_delimiter)
		return ;
	heredoc_content = read_heredoc_lines(processed_delimiter, data);
	free(processed_delimiter);
	write_to_file(heredoc_content, data->fd);
}
