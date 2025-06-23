/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:10:36 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/18 16:58:19 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_list_size(t_env *begin_list)
{
	int	size;

	size = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		size += 1;
	}
	return (size);
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	m;

	i = 0;
	m = c;
	while (s[i] != '\0')
	{
		if (s[i] == m)
			return ((char *)&s[i]);
		i++;
	}
	if (m == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

t_env	*ft_lstnew(void *content)
{
	t_env	*nw_node;

	nw_node = (t_env *)malloc(sizeof(t_env));
	if (nw_node == NULL)
		return (NULL);
	nw_node->value = content;
	nw_node->next = NULL;
	return (nw_node);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*current;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current ->next != NULL)
	{
		current = current->next;
	}
	current ->next = new;
}

// void ft_free(t_env **list)
// {
// 	t_env *tmp;

// 	tmp = *list;
// 	t_env *tmp2;
// 	while(tmp)
// 	{
// 		free(tmp->key);
// 		free(tmp->value);
// 		tmp2 = tmp;
// 		free(tmp);
// 		tmp = tmp2;
// 		tmp = tmp->next;
// 	}
// }