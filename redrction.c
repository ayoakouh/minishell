/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redrction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:59:21 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/26 16:21:47 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && big[i + j] == little[j] && (i + j) < len)
		{
			j++;
		}
		if (little[j] == '\0')
		{
			return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

int	dup_herdoc(t_redir *red)
{
	if (red->fd[1] > 0)
	{
		dup2(red->fd[1], 0);
		close(red->fd[1]);
		red->fd[1] = -1;
	}
	else
		return (-1);
	return (0);
}

int	dup_input(t_redir *tmp)
{
	if (tmp->fd[0] > 0)
	{
		dup2(tmp->fd[0], 0);
		close(tmp->fd[0]);
		tmp->fd[0] = -1;
	}
	else
		return (-1);
	return (0);
}

int	dup_output(t_redir *tmp)
{
	if (tmp->fd[0] > 0)
	{
		dup2(tmp->fd[0], 1);
		close(tmp->fd[0]);
		tmp->fd[0] = -1;
	}
	else
		return (-1);
	return (0);
}

int	ft_redircte(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == 3 && dup_herdoc(tmp) == -1)
			return (-1);
		else if (tmp->type == 0 && dup_input(tmp) == -1)
			return (-1);
		else if ((tmp->type == 1 || tmp->type == 2)
			&& dup_output(tmp) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}
