/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:50:32 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/26 18:46:25 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_print_error(t_cmd **cmd, char *str, int i)
{
	if (i == 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		perror(" ");
	}
	if (i == 1)
	{
		write(2, "minishell: ", 11);
		write(2, (*cmd)->args[0], ft_strlen((*cmd)->args[0]));
		write(2, ": is a directory\n", 17);
		(*cmd)->data.exit_status = get_or_set(SET, 126);
		exit(126);
	}
}

char	*setup_string(char *str)
{
	int		i;
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	i = 0;
	while (len > 0)
	{
		if (str[len] == '/')
			break ;
		len--;
	}
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	while (i < len && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

int	check_home(t_env **list, char *str)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, "HOME") == 0)
		{
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (tmp && tmp->value)
		{
			if ((tmp && str == NULL && tmp->key
					&& ft_strcmp(tmp->value, "") == 0)
				|| (tmp && !tmp->value))
				return (0);
		}
	}
	return (1);
}

char	*check_pwd(t_env **list, char *str, char *old_pwd)
{
	static char	*new_pwd;
	char		*tmp;

	write(2, "minishell: cd: error retrieving current directory\n", 50);
	if (old_pwd[ft_strlen(old_pwd) - 1] != '/')
	{
		tmp = ft_strjoin(old_pwd, "/");
		if (!tmp)
			return (NULL);
		new_pwd = ft_strjoin(tmp, str);
		free(tmp);
	}
	else
	{
		new_pwd = ft_strjoin(old_pwd, str);
		if (!new_pwd)
			return (NULL);
	}
	updat_env(list, "PWD", new_pwd);
	return (new_pwd);
}

int	home_not_set(char *new_cwd)
{
	if (!new_cwd)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
}
