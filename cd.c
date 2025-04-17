/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:29:34 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/15 20:34:21 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while(s1[i] || s2[i])
    {
        if(s1[i] > s2[i])
            return(1);
        if(s1[i] < s2[i])
            return (-1);
            i++;
    }
    return(0);
}
void updat_env(t_env **env_list, char *key, char *value)
{
    t_env *tmp;
    t_env *new_node;

    tmp = *env_list;
    while(tmp)
    {
        if(strcmp(key, tmp->key) == 0)
        {
            free(tmp->value);
            tmp->value = strdup(value);
            return ;
        }
        tmp = tmp->next;
    }
    new_node = malloc(sizeof(t_env));
    if(!new_node)
        return ;
    new_node = *env_list;
    new_node->key = strdup(key);
    new_node->value = strdup(key);
    *env_list = new_node;
}
char *get_key_env(char *key, t_env **list)
{
    t_env   *tmp;

    tmp = *list;
    while(tmp)
    {
        if(ft_strcmp(tmp->key, key) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}
// char *handel_path()
// void set_value_env(t_env **env, char *key, char *value)
// {
//     t_env *tmp;

//     tmp = *env;
//     // while(tmp)
//     // {
//     //     if(ft_strcmp(tmp->key, ))
//     // }
// }
int cd (char **arg, t_env **env)
{
    char cwd[1024];
    static char *oldpwd;
    char *path;
    int i = 0;

    if(!arg[1] || ft_strcmp(arg[1], "~"))
        path = get_key_env("HOME", env);
    else
        path = arg[1];
    if(!path || chdir(path) == -1)
    {
            perror("minishell: cd");
            return (1);
    }
    if (getcwd(cwd, sizeof(cwd)))
    {
        if (oldpwd)
            free(oldpwd);
        oldpwd = strdup(cwd);
        update_env("PWD", cwd, env);
    }
    return (0);
}   

void f()
{
    system("leaks a.out");
}
// int main(int ac, char **av)
// {
//     atexit(f);
//     t_env **head;
//     t_env *node1;
//     t_env *node2;
//     t_env *node3;

//     node1 = malloc(sizeof(t_env));
//     node2 = malloc(sizeof(t_env));
//     node3 = malloc(sizeof(t_env));

//     node1->key = strdup("pwd");
//     node1->value = strdup("0000");
//     node2->key = strdup("ali");
//     node2->value = strdup("ali");
//     node3->key = strdup("333333");
//     node3->value = strdup("333333");

//     *head = node1;
//     node1 ->next = node2;
//     node2 ->next = node3;
//     node3 ->next = NULL;

//     updat_env(head, "ali", "ayoub");

//     // t_env *tmp;
//     // tmp = *head;
//     // while(tmp)
//     // {
//     //     printf("key is : %s\n", tmp->key);
//     //     printf("value is : %s\n", tmp->value);
//     //     tmp = tmp->next;
//     // }
//     puts("--------");
//     cd (av, head);
// }






// char	*find_key_env2(char *key)
// {
// 	t_env	*tmp;

// 	tmp = g_data->my_env;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->key, key))
// 			return (tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// void	set_value_env(char *key, char *value)
// {
// 	t_env	*env;

// 	env = g_data->my_env;
// 	while (env)
// 	{
// 		if (!ft_strcmp(env->key, key))
// 		{
// 			if (env->value)
// 			{
// 				fre(env->value);
// 				env->value = NULL;
// 			}
// 			env->value = ft_strjoin2(env->value, value);
// 			return ;
// 		}
// 		env = env->next;
// 	}
// }

// char	*new_cwd_env(char *str)
// {
// 	char	*path;

// 	path = NULL;
// 	if (!str || str[0] == '~')
// 	{
// 		path = find_key_env(ft_strdup("HOME"));
// 		if (!path)
// 		{
// 			exit_func(HOME_NOT_SET, NULL);
// 			return (NULL);
// 		}
// 	}
// 	else if (str[0] == '-')
// 	{
// 		path = find_key_env(ft_strdup("OLDPWD"));
// 		if (!path)
// 		{
// 			g_data->exit_status = 1;
// 			exit_func(OLDPWD_NOT_SET, NULL);
// 			return (NULL);
// 		}
// 	}
// 	if (!path)
// 		path = str;
// 	return (path);
// }

// void	handle_path(char *str)
// {
// 	char	*cwd;
// 	char	*new_cwd;

// 	new_cwd = new_cwd_env(str);
// 	if (!new_cwd)
// 		return ;
// 	if (new_cwd && chdir(new_cwd) == -1)
// 		exit_func(CHDIR, new_cwd);
// 	set_value_env("OLDPWD", find_key_env2(g_data->pwd));
// 	cwd = getcwd(NULL, 0);
// 	set_value_env("PWD", cwd);
// 	if (g_data->pwd)
// 		fre(g_data->pwd);
// 	g_data->pwd = ft_strdup(cwd);
// 	if (cwd)
// 		fre(cwd);
// 	if (str && !ft_strcmp(str, "-"))
// 		pwd();
// }

// void	cd(char **args)
// {
// 	int	i;

// 	i = -1;
// 	while (args[++i])
// 		;
// 	if (i > 2)
// 	{
// 		exit_func(CD_TOO_ARGS, NULL);
// 		return ;
// 	}
// 	if (!args[1])
// 		args[1] = NULL;
// 	handle_path(args[1]);
// }












































#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void update_env(char *key, char *value, t_env **env)
// {
//     t_env *tmp = *env;

//     while (tmp)
//     {
//         if (strcmp(tmp->key, key) == 0)
//         {
//             free(tmp->value);
//             tmp->value = strdup(value);
//             return;
//         }
//         tmp = tmp->next;
//     }
//     // If the key does not exist, add it to the environment
//     t_env *new_node = malloc(sizeof(t_env));
//     if (!new_node)
//         return;
//     new_node->key = strdup(key);
//     new_node->value = strdup(value);
//     new_node->next = *env;
//     *env = new_node;
// }

// int cd(char **args, t_env **env)
// {
//     char *path;
//     char cwd[1024];
//     static char *oldpwd = NULL;

//     if (!args[1] || strcmp(args[1], "~") == 0)
//         path = getenv("HOME");
//     else if (strcmp(args[1], "-") == 0)
//     {
//         if (!oldpwd)
//         {
//             fprintf(stderr, "minishell: cd: OLDPWD not set\n");
//             return (1);
//         }
//         path = oldpwd;
//         printf("%s\n", path);
//     }
//     else
//         path = args[1];

//     if (!path || chdir(path) != 0)
//     {
//         perror("minishell: cd");
//         return (1);
//     }

//     // Update OLDPWD and PWD
//     if (getcwd(cwd, sizeof(cwd)))
//     {
//         if (oldpwd)
//             free(oldpwd);
//         oldpwd = strdup(cwd);
//         update_env("PWD", cwd, env);
//     }
//     return (0);
// }
// int cd(char *path)
// {
//     char *home;

//     if (path == NULL)
//     {
//         home = getenv("HOME"); 
//         if (home == NULL)
//         {
//             perror("cd");
//             return (1); 
//         }
//         path = home;
//     }

//     if (chdir(path) == -1)
//     {
//         perror("cd");
//         return (1);
//     }
//     return (0);
// }
// int main(int ac, char **av)
// {
//     if(ac < 0)
//         return (0);
        
//     int r = cd(av[2]);
// }