/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:34:07 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 17:26:27 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value_env(char *key, t_env **list)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	set_value_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			free(value);
			tmp->is_not_active = 0;
			return ;
		}
		tmp = tmp->next;
	}
}

void	updat_env(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env_list;
	while (tmp)
	{
		if (strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			tmp->is_not_active = 0;
			return ;
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->is_not_active = 0;
	new_node->next = NULL;
	ft_lstadd_back(env_list, new_node);
}

char	*get_set(char *type, int flag)
{
	static char	*pwd;

	if (flag == 0 && type)
	{
		if (pwd)
			free(pwd);
		pwd = ft_strdup(type);
	}
	return (pwd);
}

int	pwd(t_cmd *cmd)
{
	char	*pwd;
	int		status;

	status = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = get_set(NULL, 1);
		if (!pwd)
			perror("pwd");
		else
			printf("%s\n", pwd);
		return (status);
	}
	else
	{
		cmd->data.new_pwd = get_set(pwd, 0);
		printf("%s\n", pwd);
	}
	free (pwd);
	return (status);
}

// int pwd(t_cmd *cmd)
// {
// 	char	*pwd;
// 	int		status;

// 	status = 0;
// 	pwd = getcwd(NULL, 0);
// 	if(!pwd)
// 	{
// 		pwd = cmd->data.new_pwd;
// 		printf("%s\n", pwd);
// 		return(status);
// 	}
// 	else
// 	{
// 		cmd->data.new_pwd = pwd;
// 		printf("%s\n", pwd);
// 	}
// 	free(pwd);
// 	return (status);
// }
