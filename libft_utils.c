/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:10:36 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/10 14:05:11 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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