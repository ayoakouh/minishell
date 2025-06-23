/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:17:43 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/19 12:02:11 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*process_redir(char *str, int *pos)
{
	int	start;
	int	i;
	int	quote_state;
	int	after_operator;

	start = *pos;
	i = start + 1;
	process_redir_hp(str, &start, &i, &after_operator);
	if (!str[i] || (str[i] == '>' || str[i] == '<'))
	{
		*pos = after_operator;
		return (ft_substr(str, start, after_operator - start));
	}
	quote_state = 0;
	while (str[i])
	{
		process_redir_helper(str[i], &quote_state);
		if (quote_state == 0
			&& (str[i] == ' ' || str[i] == '<' || str[i] == '>'))
			break ;
		i++;
	}
	*pos = i;
	return (ft_substr(str, start, i - start));
}

static int	find_redir(char *str, int i)
{
	int	quote_state;

	quote_state = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && quote_state == 0)
			quote_state = 1;
		else if (str[i] == '\'' && quote_state == 1)
			quote_state = 0;
		else if (str[i] == '\"' && quote_state == 0)
			quote_state = 2;
		else if (str[i] == '\"' && quote_state == 2)
			quote_state = 0;
		else if (quote_state == 0 && (str[i] == '<' || str[i] == '>'))
			return (i);
		i++;
	}
	return (i);
}

static char	*join_redir(char *result, char *temp)
{
	char	*redir;
	char	*new_result;

	if (result)
	{
		redir = ft_strjoin(result, " ");
		free(result);
		if (!redir)
		{
			free(temp);
			return (NULL);
		}
		new_result = ft_strjoin(redir, temp);
		free(redir);
		free(temp);
		if (!new_result)
			return (NULL);
		return (new_result);
	}
	else
		return (temp);
}

char	*redir_extracter(char *str)
{
	int		i;
	char	*temp;
	char	*result;

	i = 0;
	result = NULL;
	if (!str)
		return (NULL);
	while (str[i])
	{
		i = find_redir(str, i);
		if (str[i] == '<' || str[i] == '>')
		{
			temp = process_redir(str, &i);
			result = join_redir(result, temp);
		}
		else
			break ;
	}
	if (!result)
		result = ft_substr("", 0, 0);
	return (result);
}

t_split_helper	*split_param(size_t *i, size_t *j, size_t *start)
{
	t_split_helper	*split_paramter;

	split_paramter = malloc(sizeof(t_split_helper));
	if (!split_paramter)
		return (NULL);
	split_paramter->i = i;
	split_paramter->j = j;
	split_paramter->start = start;
	return (split_paramter);
}
