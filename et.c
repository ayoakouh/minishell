
#include "minishell.h"

char *check_path(t_env **list)
{
    t_env *tmp;

    if (!list || !*list)
        return (NULL);
        
    tmp = *list;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, "PATH"))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void    ft_free_split(char **str)
{
    int i = 0;

    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void ft_excute_commands(char **args, t_env **list)
{
    char **help;
    pid_t child_pid;
    char **split_path;
    char *helper;
    char *path;
    int i = 0;
    int status;

    help = convert_env_list(list);

    if (!args || !args[0])
        return;
    if (ft_strchr(args[0], '/'))
    {
        child_pid = fork();
        if (child_pid == 0)
        {
            if(!(access(args[0], X_OK) == -1))
            {
                execve(args[0], args, help);
            }
            write(1, "command not found\n", 18);
        }
        else if (child_pid > 0)
            wait(&status);
        return;
    }
    path = check_path(list);
    if (!path)
    {
        write(2, "PATH not found\n", 15);
        return;
    }
    
    split_path = ft_split(path, ':');
    if (!split_path)
        return;
        
    child_pid = fork();
    if (child_pid == 0)
    {
        while (split_path[i])
        {
            char *tmp = ft_strjoin(split_path[i], "/");
            helper = ft_strjoin(tmp, args[0]);
            free(tmp);
            if (!helper)
            {
                i++;
                continue;
            }
            if(!(access(helper, X_OK) == -1))
            {
                execve(helper, args, help);
            }
            free(helper);
            i++;
        }
        i = 0;
        write(2, "command not found\n", 18);
        ft_free_split(split_path);
        exit(127);
    }
    else if (child_pid > 0)
    {
        wait(&status);
        ft_free_split(split_path);
    }
    else
    {
        perror("fork failed");
        ft_free_split(split_path);
    }
}
// #include "minishell.h"

// char *check_path(t_env **list)
// {
//     t_env *tmp;

//     if (!list || !*list)
//         return (NULL);
        
//     tmp = *list;
//     while (tmp)
//     {
//         if (!ft_strcmp(tmp->key, "PATH"))
//             return (tmp->value);
//         tmp = tmp->next;
//     }
//     return (NULL);
// }

// void    ft_free_split(char **str)
// {
//     int i = 0;

//     while(str[i])
//     {
//         free(str[i]);
//         i++;
//     }
//     free(str);
// }
// // char **convert_env
// void ft_excute_commands(char **args, t_env **list)
// {
//     pid_t child_pid;
//     char **split_path;
//     char *helper;
//     char *path;
//     int i = 0;
//     int status;

//     if (!args || !args[0])
//         return;
//     // if (ft_strchr(args[0], '/'))
//     // {
//     //     child_pid = fork();
//     //     if (child_pid == 0)
//     //     {
//     //         if (execve(args[0], args, NULL) == -1)
//     //         {
//     //             write(2, "command not found\n", 18);
//     //             // exit(127);
//     //         }
//     //     }
//     //     else if (child_pid > 0)
//     //         wait(&status);
//     //     return;
//     // }
//     // char **help = convert_env_list(list);
//     printf("heeel\n");
//     path = check_path(list);
//     if (!path)
//     {
//         write(2, "PATH not found\n", 15);
//         return;
//     }
//     split_path = ft_split(path, ':');
//     if (!split_path)
//         return;
        
//     child_pid = fork();
//     printf("%s\n", args[0]);
//     if (child_pid == 0)
//     {
//         while (split_path[i])
//         {
//             char *tmp = ft_strjoin(split_path[i], "/");
//             helper = ft_strjoin(tmp, args[0]);
//             free(tmp);
            
//             if (!helper)
//             {
//                 i++;
//                 continue;
//             }
//             if(execve(helper, args, NULL) == -1)
//             {
//                 write(2, "command111 not found\n", 21);
//                 // exit(127);
//             }
//             free(helper);
//             i++;
//         }
//         i = 0;
//         write(2, "command not found\n", 18);
//         ft_free_split(split_path);
//         // exit(127);
//     }
//     // else if (child_pid > 0)
//     // {
//     //     wait(&status);
//     //     exit(0);
//     //     // ft_free_split(split_path);
//     // }
//     else
//     {
//         perror("fork failed");
//         ft_free_split(split_path);
//     }
// }