/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:33:17 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/15 15:43:37 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */






#include "minishell.h"

// int ft_strcmp(char *s1, char *s2)
// {
//     int i = 0;
//     while(s1[i] || s2[i])
//     {
//         if(s1[i] > s2[i])
//             return(1);
//         if(s1[i] < s2[i])
//             return(-1);
//         i++;
//     }
//     return(0);
// }

void del(void *content)
{
    free(content);
}

int remove_env(t_env **env_list, char *variable)
{
    t_env *tmp;
    t_env *to_delete;

    if (!*env_list)
        return (0);
    
    // Special case: if first node matches
    if (ft_strcmp((*env_list)->key, variable) == 0)
    {
        to_delete = *env_list;
        *env_list = (*env_list)->next;
        del(to_delete->key);
        del(to_delete->value);
        free(to_delete);
        return (1);
    }
    
    // Check rest of list
    tmp = *env_list;
    while (tmp->next)
    {
        if (ft_strcmp(tmp->next->key, variable) == 0)
        {
            to_delete = tmp->next;
            tmp->next = tmp->next->next;
            del(to_delete->key);
            del(to_delete->value);
            free(to_delete);
            return (1);
        }
        tmp = tmp->next;
    }
    
    return (0); // Variable not found
}

void ft_unset(t_env **env_list, char *variables)
{
    // int i;
    
    // if (!variables)
    //     return;
    
    // i = 0;
    // while (variables[i])
    // {
        remove_env(env_list, variables);
    //     i++;
    // }
}
// #include "minishell.h"

// int    ft_strcmp(char *s1, char *s2)
// {
//     int i = 0;
//     while(s1[i] || s2[i])
//     {
//         if(s1[i] > s2[i])
//             return(1);
//         if(s1[i] < s2[i])
//             return (-1);
//             i++;
//     }
//     return(0);
// }
// void del(void *content)
// {
//     free(content);
// }
// char *remove_env(t_env **env_list, char *variable)
// {
//     t_env   *tmp;

//     if(!*env_list)
//         return ;
//     tmp = *env_list;
//     while(tmp)
//     {
//         if(ft_strcmp(tmp->next->key, variable) == 0)
// 		{
            
// 			del(tmp->key);
// 			del(tmp->value);
//             free(tmp);
//             return ()
// 		}
//         tmp = tmp->next;
//     }
// }

// void ft_unset(t_env **env_list, char *variable)
// {
//     t_env *temp;

//     remove_env(env_list, variable);    

// }