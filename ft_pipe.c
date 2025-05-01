// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_pipe.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/26 17:34:56 by ayoakouh          #+#    #+#             */
// /*   Updated: 2025/04/27 15:29:24 by ayoakouh         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"
char    *ft_strcpy(char *s1, char *s2)
  {
      int i;
 
      i = 0;
      while (s2[i])
      {
          s1[i] = s2[i]; // so this will make s1 = to whatever s2 is looping through the string
          i++;
      }
      s1[i] = s2[i];  // now that we are finsihing looping though s1[i] will equal s2[i]
      return (s1);
  }
char **convert_env_list(t_env **list)
{
    t_env * tmp;
    char **helper = NULL;
    char *str;
    char *temp;
    int  i = 0;
    tmp = *list;
    int len = ft_list_size(*list);

    helper = malloc(sizeof(char *) * (len + 1));
    while(tmp)
    {
        str = ft_strdup(tmp->key);
        temp = ft_strjoin(str, "=");
        free(str);
        str = ft_strjoin(temp, tmp->value);
        free(temp);
        helper[i] = ft_strdup(str);
        free(str);
        tmp = tmp->next;
        i++;
    }
    helper[i] = NULL;
    return (helper);
}
void ft(char **args, t_env **list) // pipe moust be check and access;;;;*
{
    char **split_path;
    char **helper;
    char *path;
    int i= 0;
    char *tmp;

    helper = convert_env_list(list);
    path = check_path(list);
    if(!args || !args[0])
        return ;
    if(ft_strchr(args[0], '/'))
    {
        if(!(access(args[0], X_OK) == -1))
        {
            execve(args[0], args, helper);
        }
        write(1, "command not found\n", 18);
    }
    else
    {
        split_path = ft_split(path, ':');
        if(!split_path)
            return ;
        while(split_path[i])
        {
            tmp = ft_strjoin(split_path[i], "/");
            char *str = ft_strjoin(tmp, args[0]);
            free(tmp);
            if (!helper)
            {
                i++;
                continue;
            }
            if(!(access(str, X_OK) == -1))
            {
                execve(str, args, helper);
            }
            free(str);
            i++;
        }
        i = 0;
        write(2, "command not found\n", 18);
        ft_free_split(split_path);
        exit(127);
    }        
}
void    pipe_all(t_cmd *head)
{
    t_cmd *cmd = head;

    while (cmd)
    {
        if (cmd->pipe_out)
        {
            pipe(cmd->fd_pipe); // creates cmd->fd_pipe[0] (read) and [1] (write)
            // return (cmd->fd_pipe);
        }
        cmd = cmd->next;
    }
}

int		list_size(t_cmd *begin_list)
{
	int		size;
	
    size = 0;
    while (begin_list)
    {
        begin_list = begin_list->next;
        size += 1;
    }
	return (size);
}

void    close_parent_pipe(t_cmd *tmp)
{
    while(tmp && tmp->pipe_out != 0)
    {
        close(tmp->fd_pipe[0]);
        close(tmp->fd_pipe[1]);
        tmp = tmp->next;
    }

}
void ft_excute_mult_pipe(t_cmd *cmd, t_env *list_env, char *env[])
{
    pid_t pid1;
    t_cmd *prev = NULL;
    t_cmd  *tmp;

    tmp = cmd;
    cmd->total_pipes = list_size(cmd) - 1;
    pipe_all(cmd);

    while (cmd)
    {
        pid1 = fork();
        if (pid1 < 0)
            perror("error");
        else if (pid1 == 0)  // Child process
        {
            if (cmd->pipe_out == 1 && prev == NULL)
            {
                close (cmd->fd_pipe[0]);
                dup2(cmd->fd_pipe[1], 1);
                close (cmd->fd_pipe[1]);
            }
            else if (cmd->pipe_out == 1 && prev != NULL)
            {
                close (cmd->fd_pipe[0]);
                close(prev->fd_pipe[1]);
                dup2(prev->fd_pipe[0], 0);
                close(prev->fd_pipe[0]);
                dup2(cmd->fd_pipe[1], 1);
                close(cmd->fd_pipe[1]);
            }   
            else if (cmd->pipe_out == 0 && prev != NULL)
            {
                close (prev->fd_pipe[1]);
                dup2(prev->fd_pipe[0], 0);
                close(prev->fd_pipe[0]);
            }
            ft(cmd->args, &list_env);
            // ft_excute_commands(cmd->args, &list_env);
        }
        prev = cmd;
        cmd = cmd->next;
    }
    close_parent_pipe(tmp);
    while (wait(NULL) > 0)
        ;
    // close();
}

// void child_proceess(t_cmd *cmd, t_env *env, char **en)
// {
//     // int status = 0;
//     pid_t pid1;    
//     pid1 = fork();
//     if(pid1 == -1)
//         printf("fork is fails\n");
//     else if(pid1 == 0)
//     {
//         close(cmd->fd_pipe[0]);
//        dup2(cmd->fd_pipe[1], 1);
//        close (cmd->fd_pipe[1]);
//         if(!is_builtin(cmd->args))
//             excute_builting(&cmd, env, en);
//         else
//         {

//             ft_excute_commands(cmd->args, &env);
//         }
//         exit(0);
//     }
//         // waitpid(pid1, NULL, 0);
//     // exit(EXIT_FAILURE);
    
// }

// void secand_processe(t_cmd *cmd, t_env *env, char **en)
// {
//     // int status = 0;
//     pid_t pid2;
//     pid2 = fork();
//     if (pid2 == -1)
//         printf("ERROR\n");
//     else if (pid2 == 0)
//     {
//         close (cmd->fd_pipe[1]);
//         dup2(cmd->fd_pipe[0], 0);
//         close(cmd->fd_pipe[0]);
//         if(!is_builtin(cmd->next->args))
//         {
//             excute_builting(&cmd->next, env, en);
//         }
//         else
//             ft_excute_commands(cmd->next->args, &env);
//         exit (0);
//     }
//     // waitpid(pid2, NULL, 0);
//     // exit(EXIT_FAILURE);
// }
// void ft_excute_pipe(t_cmd *cmd, t_env *env, char **en)
// {
//     // int fd_input;
//     // int fd_output;
//     // int fd[2];
//     // pid_t pid1;
//     // pid_t pid2;

//     // fd_input = dup(0);
//     // fd_output = dup(1);

//     if(pipe(cmd->fd_pipe) == -1)
//         printf("ERROR\n");
//     child_proceess(cmd, env, en);
//     secand_processe(cmd, env, en);
//     // while(wait(NULL) > 1);
//     // exit(0);
//     wait(NULL);
//     // exit(0);
// }
// #include "minishell.h"........................................0

// void child_proceess(t_cmd *cmd, t_env *env, char **en)
// {
//     pid_t pid1;    
//     pid1 = fork();
//     if(pid1 == -1)
//         printf("fork is fails\n");
//     else if(pid1 == 0)
//     {
//         close(cmd->fd_pipe[0]);
//         dup2(cmd->fd_pipe[1], 1);
//         // close(cmd->fd_pipe[1]);
        
//         // if(!is_builtin(cmd->args))
//         //     excute_builting(&cmd, env, en);
//         // else
//             ft(cmd->args, &env);
        
//         exit(0);
//     }
//     // wait (NULL);
// }

// void secand_processe(t_cmd *cmd, t_env *env, char **en)
// {
//     pid_t pid2;

//     pid2 = fork();
//     if (pid2 == -1)
//         printf("ERROR\n");
//     else if (pid2 == 0)
//     {
//         close(cmd->fd_pipe[1]);
//         dup2(cmd->fd_pipe[0], 0);
//         // close(cmd->fd_pipe[0]);
//         // if(!is_builtin(cmd->next->args))
//         //     excute_builting(&cmd->next, env, en);
//         // else
//             ft(cmd->next->args, &env);
//         // wait (NULL);
//         exit(0);
//     }

// }

// void ft_excute_pipe(t_cmd *cmd, t_env *env, char **en)
// {
//     if(pipe(cmd->fd_pipe) == -1)
//         printf("ERROR\n");
//     child_proceess(cmd, env, en);
//     secand_processe(cmd, env, en);
//     while (waitpid(-1, NULL, 0) > 0)
//         ;
//     // Don't exit here - remove the exit(EXIT_FAILURE)
// }