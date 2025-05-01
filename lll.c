/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:22:58 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/26 10:42:08 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int exec_builtin(char **args)
{
    if (strcmp(args[0], "cd") == 0)
        return (0);
    else if (strcmp(args[0], "echo") == 0)
        return (0);
    else if (strcmp(args[0], "unset") == 0)
        return (0);
    else if (strcmp(args[0], "export") == 0)
        return (0);
        else if (strcmp(args[0], "pwd") == 0)
            return (0);
        else if (strcmp(args[0], "env") == 0)
            return (0);
        else if (strcmp(args[0], "exit") == 0)
            return (0);
        else
            return (1);
}
void minishell_cmd(char *env[])
{
    pid_t pid = fork();
if (pid == 0)
{
    char *args[] = {"./minishell", NULL};
    execve("./minishell", args, env);
}
else
{
    waitpid(pid, NULL, 0);
}

}
// void f()
// {
//     system("leaks minishell");
// }
// void check_line(char *line, t_cmd **command, t_env *env, char *en[])
// {
//     char **splited;
//     int        i;
    
//     atexit(f);
//     i = 0;
//     splited = ft_split(line, ' ');
//     t_cmd *cmd;
//     if(!exec_builtin(splited))
//     {
//         while (splited[i])
//         {
//             if (strncmp("export", splited[i], 6) == 0 && strlen(splited[i]) == 6)
//                 ft_export(splited, &env);
//             else if (strncmp("env", splited[i], 3) == 0 && strlen(splited[i]) == 3)
//                 ft_env(env, en);
//             else if (strncmp("exit", splited[i], 4) == 0 && strlen(splited[i]) == 4)
//                 ft_exit(splited);
//             else if (strncmp("./minishell", splited[i], 11) == 0 && strlen(splited[i]) ==  11)
//             {
//                 ft_free_split(splited);
//                 minishell_cmd(en);
//             }
//             else if (strncmp("unset", splited[i], 5) == 0 && strlen(splited[i]) == 5)
//                 ft_unset(&env, splited + 1);
//             else if (strncmp("echo", splited[i], 4) == 0 && strlen(splited[i]) == 4)
//                 echo(splited);
//             else if (strncmp("pwd", splited[i], 3) == 0 && strlen(splited[i]) == 3)
//                 pwd();
//             else if (strncmp("cd", splited[i], 2) == 0 && strlen(splited[i]) == 2)
//                 ft_cd(splited, &env);
//             i++;
//         }
//         ft_free_split(splited);
//     }
//     else
//         ft_excute_commands(splited, &env);
// }

// int main(int argc, char *argv[], char *env[])
// {
//     t_env    *env_new = NULL;
//     char    *line;


//     (void)argv;
// 	(void)argc;
//     // int i = 0;
//     // while(env[i])
//     // {
//     //     printf("%s\n", env[i]);
//     //     i++;
//     // }
//     // if (!env || !*env)
//     //     return (1);
//     // if (argc < 0)
//     //     return (0);
// 	env_new = env_maker(env, &env_new);
//     // env_new = creat_env(env);
//     // print_strcut(env_new);
//     // env_cmd(env_new);
//     // export(&env_new, argv[1]);
//     // env_cmd(env_new);
// 	// t_env *tmp = 
//     // t_cmd **cmd;
//     // t_cmd *tmp;

//     // tmp->

//     // intialize_struct
//     while (1)
//     {
//       line = readline("minishell-> ");
//       if (!line || !*line)
//       {
//         write (2, "exit\n", 6);
//         break;
//       }
//       add_history(line);
//       check_line(line, env_new, env);
//     }
    
// }


















// void check_line(char *line, t_env *env, char *en[])
// {
//     char **splited;
//     int i;
    
//     // atexit(f);
//     i = 0;
//     splited = ft_split(line, ' ');
    
//     // // Allocate memory for cmd structure
//     // t_cmd *cmd = malloc(sizeof(t_cmd));
//     // if (!cmd)
//     // {
//     //     perror("malloc failed");
//     //     ft_free_split(splited);
//     //     return;
//     // }
    
//     // // Initialize cmd structure
//     // cmd->cmd = splited[0] ? strdup(splited[0]) : NULL;
//     // cmd->args = splited;
//     // cmd->redirs = NULL;
//     // cmd->pipe_out = 0;
//     // cmd->next = NULL;
    
//     if(!exec_builtin(splited))
//     {
//         while (splited[i])
//         {
//             if (strncmp("export", splited[i], 6) == 0 && strlen(splited[i]) == 6)
//                 ft_export(splited, &env);
//             else if (strncmp("env", splited[i], 3) == 0 && strlen(splited[i]) == 3)
//                 ft_env(env, en);
//             else if (strncmp("exit", splited[i], 4) == 0 && strlen(splited[i]) == 4)
//                 ft_exit(splited);
//             // else if (strncmp("./minishell", splited[i], 11) == 0 && strlen(splited[i]) ==  11)
//             // {
//             //     ft_free_split(splited);
//             //     minishell_cmd(en);
//             // }
//             else if (strncmp("unset", splited[i], 5) == 0 && strlen(splited[i]) == 5)
//                 ft_unset(&env, splited + 1);
//             else if (strncmp("echo", splited[i], 4) == 0 && strlen(splited[i]) == 4)
//                 echo(splited);
//             else if (strncmp("pwd", splited[i], 3) == 0 && strlen(splited[i]) == 3)
//                 pwd();
//             else if (strncmp("cd", splited[i], 2) == 0 && strlen(splited[i]) == 2)
//                 ft_cd(splited, &env);
//             i++;
//         }
//         ft_free_split(splited);
//     }
//     // else
//     // {
//     //     // Check for redirections in the command line
//     //     // This is a simple check - you'd need more parsing for real redirection detection
//     //     for (i = 0; splited[i]; i++)
//     //     {
//     //         if (strcmp(splited[i], "<") == 0 && splited[i+1])
//     //         {
//     //             // Create input redirection
//     //             t_redir *redir = malloc(sizeof(t_redir));
//     //             if (redir)
//     //             {
//     //                 redir->type = 0;  // Input redirection
//     //                 redir->fd_file = strdup(splited[i+1]);
//     //                 redir->next = cmd->redirs;
//     //                 cmd->redirs = redir;
//     //             }
//     //         }
//     //         else if (strcmp(splited[i], ">") == 0 && splited[i+1])
//     //         {
//     //             // Create output redirection
//     //             t_redir *redir = malloc(sizeof(t_redir));
//     //             if (redir)
//     //             {
//     //                 redir->type = 1;  // Output redirection
//     //                 redir->fd_file = strdup(splited[i+1]);
//     //                 redir->next = cmd->redirs;
//     //                 cmd->redirs = redir;
//     //             }
//     //         }
//     //     }
        
//     //     // If there are redirections, handle them
//     //     if (cmd->redirs)
//     //     {
//     //         // Create a copy of the command to execute with redirections
//     //         pid_t pid = fork();
//     //         if (pid == 0)
//     //         {
//     //             ft_redircte(&cmd);
//     //             exit(0);
//     //         }
//     //         else
//     //         {
//     //             waitpid(pid, NULL, 0);
//     //         }
            
//     //         // Free redirection structures
//     //         t_redir *curr = cmd->redirs;
//     //         while (curr)
//     //         {
//     //             t_redir *next = curr->next;
//     //             free(curr->fd_file);
//     //             free(curr);
//     //             curr = next;
//     //         }
//     //     }
//         else
//         {
//             // Execute command normally
//             ft_excute_commands(splited, &env);
//         }
//     }



// // int main(int ac, char **av, char *env[])
// // {
// // 	t_env *tmp = NULL;
// //     if(ac < 0)
// // 	{
// //         return 0;
// // 	}
// // 	ft_export(env, av, &tmp);
// // }
// 	// t_env *head;
// 	// t_env *node1;
// 	// t_env *node2;
// 	// t_env *node3;
	
// 	// node1 = malloc(sizeof(t_env));
// 	// node2 = malloc(sizeof(t_env));
// 	// node3 = malloc(sizeof(t_env));

// 	// node1->key = strdup("PWD");
// 	// node1->value = strdup("/ayoub/");
// 	// node2->key = strdup("HOME");
// 	// node2->value = strdup("/mnt/homes/ayoakouh");
// 	// node3->key = strdup("ali");
// 	// node3->value = strdup("333333");

// 	// head = node1;
// 	// node1 ->next = node2;
// 	// node2 ->next = node3;
// 	// node3 ->next = NULL;
//     // // ft_unset(&head, av[2]);
// 	// // updat_env(head, "ali", "ayoub");
// 	// // ft_cd(av[2], &head);
// 	// // cd(av);
// 	// puts("---------");
// 	// ft_exit(av);
// 	// // remove_env(&head, "ali");
// 	// t_env *tmp;
// 	// tmp = head;
// 	// // minishell_exit(av, head);
// 	// while(tmp)
// 	// {
// 	// 	printf("key is : %s\n", tmp->key);
// 	// 	printf("value is : %s\n", tmp->value);
// 	// 	tmp = tmp->next;
// 	// }
// 	// // cd (av, head);
