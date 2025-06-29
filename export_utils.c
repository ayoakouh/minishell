/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:48:15 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/26 21:35:44 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(t_env *env_list, char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*get_key(char *str)
{
	unsigned int	i;
	char			*helper;

	i = 0;
	helper = NULL;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (str[i] == '=')
			break ;
		i++;
	}
	helper = ft_substr(str, 0, i);
	if (!helper)
		return (NULL);
	return (helper);
}

void	set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new_node;
	char	*temp;

	tmp = *env;
	temp = NULL;
	new_node = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			temp = tmp->value;
			tmp->value = ft_strjoin(tmp->value, value);
			free (temp);
			return ;
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	ft_lstadd_back(env, new_node);
}

int	env_helper(t_env **head)
{
	if (!(*head)->key || !(*head)->next || !(*head)->next->key)
	{
		*head = (*head)->next;
		return (1);
	}
	return (0);
}

t_env	*sort_env(t_env **head)
{
	t_env	*helper;
	char	*tmp_key;
	char	*tmp_value;

	if (!head || !*head)
		return (NULL);
	helper = *head;
	while (head != NULL && *head != NULL && (*head)->next != NULL)
	{
		if (env_helper(head) == 1)
			continue ;
		if (ft_strcmp((*head)->key, (*head)->next->key) > 0)
		{
			tmp_key = (*head)->key;
			tmp_value = (*head)->value;
			(*head)->key = (*head)->next->key;
			(*head)->value = (*head)->next->value;
			(*head)->next->key = tmp_key;
			(*head)->next->value = tmp_value;
			*head = helper;
		}
		else
			*head = (*head)->next;
	}
	return (helper);
}
