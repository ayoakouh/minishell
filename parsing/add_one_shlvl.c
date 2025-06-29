/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_one_shlvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:07:38 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/28 15:11:55 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_one_shlvl(t_env *env)
{
	t_env	*shlvl_node;

	if (!env)
		return ;
	shlvl_node = find_shlvl_node(env);
	if (shlvl_node)
		update_shlvl_value(shlvl_node);
	else
		add_shlvl_node(env);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	if (d > s)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	else
	{
		ft_memcpy(d, s, n);
	}
	return (dest);
}

t_env	*find_last_node(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	count_nodes(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	check_node(t_cmd *cmd, int i)
{
	if (i != 1 && cmd->next == NULL)
		return (1);
	return (0);
}
