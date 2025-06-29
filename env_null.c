/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_null.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:58:55 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:47:28 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_key(char *str, char *key, int *status)
{
	if (is_valid_key(key) == 1)
	{
		printf("minishell: export: %s : not valid identifier\n", str);
		*status = 1;
		return (1);
	}
	return (0);
}

int	check_append(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			return ('+');
		}
		else if (str[i] == '=')
		{
			return ('=');
		}
		i++;
	}
	return (0);
}

t_env	*creat_new_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	if (!ft_strcmp(key, "OLDPWD"))
		new_node->is_not_active = 1;
	new_node->next = NULL;
	return (new_node);
}

t_env	*env_null(void)
{
	t_env	*tmp;
	t_env	*list;

	list = NULL;
	tmp = creat_new_env(
			ft_strdup("PATH"),
			ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	ft_lstadd_back(&list, tmp);
	ft_lstadd_back(&list, creat_new_env(ft_strdup("OLDPWD"), NULL));
	ft_lstadd_back(&list, creat_new_env(ft_strdup("PWD"), getcwd(NULL, 0)));
	ft_lstadd_back(&list, creat_new_env(ft_strdup("SHLVL"), ft_strdup("1")));
	return (list);
}

void	value_empty(t_env **env_list, char *key)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = strdup(key);
	new_node->value = NULL;
	new_node->is_not_active = 1;
	new_node->next = NULL;
	ft_lstadd_back(env_list, new_node);
}
