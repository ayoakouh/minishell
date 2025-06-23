/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:09:10 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 17:28:38 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_export(char *str, char *key, char *value, t_env **lst)
{
	int	i;

	i = 0;
	if (check_append(str) == '+')
	{
		set_env(lst, key, value);
	}
	if (check_append(str) == '=')
	{
		updat_env(lst, key, value);
	}
	if (check_append(str) == 0)
	{
		value_empty(lst, key);
	}
}

static void	export_one(char *str, t_env **lst, int *status)
{
	char	*key;
	char	*value;

	key = get_key(str);
	if (is_invalid_key(str, key, status))
	{
		free(key);
		return ;
	}
	value = get_value(str);
	if (should_skip_export(str, lst, key, value))
	{
		return ;
	}
	process_export(str, key, value, lst);
	free(key);
	free(value);
}

int	ft_handel_export(char **str, t_env **lst)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (str[i])
	{
		export_one(str[i], lst, &status);
		i++;
	}
	return (status);
}

void	print_export(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		}
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

int	ft_export(char **str, t_env **env_list)
{
	int	status;

	status = 0;
	if (!env_list || !*env_list)
		return (0);
	*env_list = sort_env(env_list);
	if (!str[1])
	{
		if (*env_list != NULL)
			print_export(*env_list);
		return (0);
	}
	else
	{
		status = ft_handel_export(str + 1, env_list);
		return (status);
	}
}
// int	check_if_key_has_value(t_env *list, char *str, char *key)
// {
// 	if ((ft_strchr(str, '=') == NULL))
// 	{
// 		if (ft_check(list, key) == 1)
// 		{
// 			return (1);
// 		}
// 		else
// 			return (0);
// 	}
// 	return (0);
// }
// int ft_handel_export(char **str, t_env **lst)
// {
// 	int i = 0;
// 	char *key = NULL;
// 	char *value = NULL;
// 	int status = 0;
// 	while(str[i])
// 	{
// 		key = get_key(str[i]);
// 		if (is_valid_key(key) == 1)
// 		{
// 			printf("minishell: export: %s : not valid identifier\n", str[i]);
// 			status = 1;
// 			free(key);
// 			i++;
// 			continue;
// 		}
// 		value = get_value(str[i]);
// 		if(check_if_key_has_value(*lst,str[i], key) == 1)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		process_export(str[i], key, value, lst);
// 		free(key);
// 		free(value);
// 		i++;
// 	}
// 	return (status);
// }
		// if ((ft_strchr(str[i], '=') == NULL))
		// {
		//    if (ft_check(*lst, key) == 1)
		//    {
		// 		i++;
		// 		continue;
		//    }
		// }