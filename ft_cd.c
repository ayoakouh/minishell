/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:05:15 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 14:54:57 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_chdir(char *new_cwd, char *str)
{
	char	*helper;
	char	*tmp;

	if (!new_cwd)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (new_cwd != NULL && chdir(new_cwd) == -1)
	{
		if (ft_strnstr(new_cwd, "..", ft_strlen(new_cwd)) != NULL)
		{
			helper = ft_strdup(get_set(NULL, 0));
			tmp = setup_string(helper);
			if (chdir(tmp) == -1)
			{
				_print_error(NULL, str, 0);
				free(tmp);
				return (1);
			}
		}
		else
		{
			_print_error(NULL, str, 0);
			return (1);
		}
	}
	return (0);
}

int	check_home(t_env **list, char *str)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
		{
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp)
	{
		if ((str == NULL && tmp && tmp->key && ft_strcmp(tmp->value, "") == 0)
			|| ( tmp && !tmp->value))
			return (0);	
	}
	return (1);
}

int	ft_cd(char **str, t_env **list, t_cmd *cmd)
{
	char	*cwd;
	char	*new_cwd;
	char	*value;
	char	*new_pw;
	t_env	*tmp;

	new_cwd = get_path(str[1], list);
	if(check_home(list, str[1]) == 0)
		return(0);
	value = get_value_env("PWD", list);
	if (ft_chdir(new_cwd, str[1]) == 1)
		return (1);
	if (value)
		set_value_env(list, "OLDPWD", value);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cmd->data.new_pwd = get_set(NULL, 1);
		if (cmd->data.new_pwd)
			new_pw = check_pwd(list, str[1], cmd->data.new_pwd);
		cmd->data.new_pwd = get_set(new_pw, 0);
		free(new_pw);
	}
	if (cwd)
		cmd->data.new_pwd = get_set(cwd, 0);
	set_value_env(list, "PWD", cmd->data.new_pwd);
	return (0);
}
		// updat_env(list, "OLDPWD", value);


		// set_value_env(list, "PWD", cmd->data.new_pwd);

	// if (!new_cwd || chdir(new_cwd) == -1)
	// {
	// 	ft_putstr_fd("minishell: cd: ", 2);
	// 	ft_putstr_fd(str[1], 2);
	// 	perror(" ");
	// 	return(1);
	// }


// static void	copy_strings(char *ptr, const char *s1, const char *s2)
// {
// 	unsigned int	i;
// 	unsigned int	j;

// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j] != '\0')
// 	{
// 		ptr[i + j] = s2[j];
// 		j++;
// 	}
// 	ptr[i + j] = '\0';
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char			*ptr;
// 	size_t			total_len;
 
// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (strdup(s2));
// 	if (!s2)
// 		return (strdup(s1));
// 	total_len = strlen(s1) + strlen(s2);
// 	ptr = (char *)malloc (sizeof(char) * (total_len + 1));
// 	if (ptr == NULL)
// 		return (NULL);
// 	copy_strings(ptr, s1, s2);
// 	return (ptr);
// }


// int	ft_cd(char **str, t_env **list)
// {
// 	char	*cwd;
// 	char	*new_cwd;


// int ft_cd(char **str, t_env **list, t_cmd *cmd)
// {
//     char *cwd;
//     char *new_cwd;
//     char *old_pwd;
//     static char *backup_pwd;

//     new_cwd = get_path(str[1], list);
//     old_pwd = get_value_env("PWD", list);

//     if (!new_cwd || chdir(new_cwd) == -1)
//     {
//         perror("minishell: cd");
//         return 1;
//     }

//     if (old_pwd)
//         updat_env(list, "OLDPWD", old_pwd);

//     cwd = getcwd(NULL, 0);
//     if (cwd)
//     {
//         set_value_env(list, "PWD", cwd);
//         backup_pwd = cwd; // keep backup in case getcwd fails later
//         cmd->data.new_pwd = cwd;
//     }
//     else
//     {
//         cmd->data.new_pwd = backup_pwd;
//         char *fixed_pwd = check_pwd(list, str[1], backup_pwd);
//         if (fixed_pwd)
//             cmd->data.new_pwd = fixed_pwd;
//     }
//     return 0;
// }
// 	char	*value;
// 	static new_pwd;

// 	new_cwd = get_path(str[1], list);
// 	value = get_value_env("PWD", list); // detsktop//cccc/0/1/2;
// 	if(!new_cwd || chdir(new_cwd) == -1)
// 	{
// 		write(2, "minishell: cd: HOME not set\n", 28);
// 		return (1);
// 	}
// 	if(value)
// 		updat_env(list, "OLDPWD", value);
// 	// set_value_env(list, "OLDPWD", value);
// 	cwd = getcwd(NULL, 0);
// 	if(!cwd)
// 	{
// 		check_pwd(new_pwd, cwd, value);
// 	}
// 	set_value_env(list, "PWD", cwd);
// 	free(cwd);
// 	return (0);
// }