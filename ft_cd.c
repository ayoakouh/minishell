/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:05:15 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/15 15:41:39 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_strings(char *ptr, const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ptr;
	size_t			total_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	total_len = strlen(s1) + strlen(s2);
	ptr = (char *)malloc (sizeof(char) * (total_len + 1));
	if (ptr == NULL)
		return (NULL);
	copy_strings(ptr, s1, s2);
	return (ptr);
}

char *get_value_env(char *key, t_env **list)
{
	t_env   *tmp;

	tmp = *list;
	while(tmp)
	{
		if(ft_strcmp(tmp->key, key) == 0)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
void    set_value_env(t_env **env, char *key, char *value)
{
	t_env *tmp;

	tmp = *env;
	while(tmp)
	{
		if(ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = NULL;
			}
			tmp->value = ft_strjoin(tmp->value, value);
			return ;
		}
		tmp = tmp->next;
	}
}

void updat_env(t_env **env_list, char *key, char *value)
{
	t_env *tmp;
	t_env *new_node;

	tmp = *env_list;
	while(tmp)
	{
		if (strcmp(key, tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return;
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	if(!new_node)
		return;
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	new_node->next = NULL;
	ft_lstadd_back(env_list, new_node);
}

char *get_path(char *str, t_env **list)
{
	char *path;

	path = NULL;
	printf("......%s\n", str);
	if(str == NULL || str[0] == '~')
	{
		printf("helle \n");
		path = get_value_env(strdup("HOME"), list); //i have smale probleme in this null;
		if(!path)
			return(NULL);
	}
	else if(!path)
	{
		path = str;
	}
	return (path);
}
void ft_cd(char *str, t_env **list)
{
	char *cwd;
	char *new_cwd;
	char *value;

	new_cwd = get_path(str, list);
	value = get_value_env("PWD", list);
	if(!new_cwd || chdir(new_cwd) == -1)
	{
		perror("error");
		return ;
	}
	updat_env(list, "OLDPWD", value);
	// set_value_env(list, "OLDPWD", get_value_env("PWD", list));
	cwd = getcwd(NULL, 0);
	set_value_env(list, "PWD", cwd);
	free(cwd);
}
// void	cd(char **args)
// {
// 	int	i;

// 	// i = -1;
// 	// while (args[++i])
// 	// 	;
// 	// if (i > 2)
// 	// {

// 	// 	return ;
// 	// }
// 	// if (!args[1])
// 	// 	args[1] = NULL;
// 	handel_path(args[2]);


// }


// int main(int ac, char **av)
// {
// 	t_env *head;
// 	t_env *node1;
// 	t_env *node2;
// 	t_env *node3;
	
// 	node1 = malloc(sizeof(t_env));
// 	node2 = malloc(sizeof(t_env));
// 	node3 = malloc(sizeof(t_env));

// 	node1->key = strdup("PWD");
// 	node1->value = strdup("/ayoub/");
// 	node2->key = strdup("HOME");
// 	node2->value = strdup("/mnt/homes/ayoakouh");
// 	node3->key = strdup("ali");
// 	node3->value = strdup("333333");

// 	head = node1;
// 	node1 ->next = node2;
// 	node2 ->next = node3;
// 	node3 ->next = NULL;
// 	// updat_env(head, "ali", "ayoub");
// 	ft_cd(av[2], &head);
// 	// cd(av);
// 	puts("---------");
// 	// remove_env(&head, "ali");
// 	t_env *tmp;
// 	tmp = head;
// 	while(tmp)
// 	{
// 		printf("key is : %s\n", tmp->key);
// 		printf("value is : %s\n", tmp->value);
// 		tmp = tmp->next;
// 	}
// 	// cd (av, head);
// }
// void updat_env(t_env **env_list, char *key, char *value) // this set_value_env;
// {
//     t_env *tmp;
//     t_env *new_node;

//     tmp = *env_list;
//     while(tmp)
//     {
//         if(strcmp(key, tmp->key) == 0)
//         {
//             free(tmp->value);
//             tmp->value = strdup(value);
//             return ;
//         }
//         tmp = tmp->next;
//     }
//     new_node = malloc(sizeof(t_env));
//     if(!new_node)
//         return ;
//     ft_lstadd_back(env_list, new_node);

//     new_node->key = strdup(key);
//     new_node->value = strdup(key);
//     // new_node->next = *env_list;
//     // *env_list = new_node;
// }