/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redrction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:59:21 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/05/01 18:04:42 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
// typedef struct s_redir
// {
//     int type;             /* 0:<, 1:>, 2:>>, 3:<< */
//     char *fd_file;
//     struct s_redir *next; /* Next redirection */
// } t_redir;

// typedef struct s_cmd
// {
//     char *cmd;            /* Command name */
//     char **args;          /* Command args (including cmd as args[0]) */
//     t_redir *redirs;      /* Redirections list */
//     int pipe_out;         /* 1 if command pipes to next */
//     struct s_cmd *next;   /* Next command in pipeline */
// } t_cmd;

void intialize_struct(t_redir *list)
{
    t_redir *tmp = list;

    tmp->type  = 0;
    tmp->file = strdup("input.txt");
}
void ft_redircte(t_redir *rederction)
{
    t_redir *tmp;
    tmp = rederction;
    int fd_input;
    int fd_outpot;
    int fd;
    // int i =0;
    // t_redir *redir = NULL;
    // tmp = redir;

    fd_input = dup(0);
    fd_outpot = dup(1);
    while(tmp)
    {
        if(tmp->type == 0)
        {
            fd = open(tmp->file, O_CREAT | O_RDONLY);
            if(fd == -1)
            {
                perror("open");
                // exit(1)
            }
                dup2(fd, 0);
                // execve(tmp->args[i], tmp->args, NULL);
                close(fd);
        }
        else if (tmp->type == 1)
        {
            fd = open(tmp->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if(fd == -1)
            {
                perror("open");
                exit(1);
            }
                dup2(fd, 1);
                // execve(tmp->args, tmp->args, NULL);
                close(fd);
        }
        else if(tmp->type == 2)
        {
            fd = open(tmp->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd == -1)
            {
                perror("open");
            }
            dup2(fd, 1);
            close (fd);
        }
        // if(tmp->args && tmp->args[0])
        // {
        //     execve(*tmp->args, &tmp->args[0], NULL);  
        // }
        tmp = tmp->next;
    }
    // close(fd_input);
    // close(fd_outpot);

    // if (tmp->type == 0)
    // {
    //     if(open())
    // }
}
// t_redir *new_redir(int type, char *file)
// {
//     t_redir *tmp = malloc(sizeof(t_redir));
//     if (!redir)
//         return NULL;
    
//     redir->type = type;
//     redir->file = strdup(file);
//     redir->next = NULL;
//     return redir;
// }

// // Function to create a new rederction
// t_cmd *new_cmd(char *cmd, char **args)
// {
//     t_cmd *command = malloc(sizeof(t_cmd));
//     if (!command)
//         return NULL;
    
//     command->cmd = strdup(cmd);
//     command->args = args;
//     command->redirs = NULL;
//     command->pipe_out = 0;
//     command->next = NULL;
//     return command;
// }

// Function to free command structure
void free_cmd(t_cmd *cmd)
{
    t_redir *redir;
    t_redir *next_redir;
    
    if (cmd->cmd)
        free(cmd->cmd);
    
    if (cmd->args)
    {
        for (int i = 0; cmd->args[i]; i++)
            free(cmd->args[i]);
        free(cmd->args);
    }
    
    redir = cmd->redirs;
    while (redir)
    {
        next_redir = redir->next;
        if (redir->file)
            free(redir->file);
        free(redir);
        redir = next_redir;
    }  
    free(cmd);
}

// int main(void)
// {
//     // Test case 1: Simple ls command with input redirection
//     printf("=== Test 1: ls with input redirection ===\n");
    
//     // Create command: ls -la
//     char **args = malloc(3 * sizeof(char *));
//     args[0] = strdup("ls");
//     args[1] = strdup("-la");
//     args[2] = NULL;
    
//     t_cmd *cmd = new_cmd("ls", args);
    
//     // Add input redirection
//     t_redir *redir = new_redir(0, "input.txt");
//     cmd->redirs = redir;
    
//     // Create a test input file
//     int fd = open("input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd != -1) {
//         write(fd, "Test input file content\n", 23);
//         close(fd);
//     }
    
//     // Execute the redirection test
//     printf("Command: %s\n", cmd->cmd);
//     printf("Arguments: %s %s\n", cmd->args[0], cmd->args[1]);
//     printf("Redirection type: %d, file: %s\n", cmd->redirs->type, cmd->redirs->fd_file);
    
//     // Instead of actually executing (which would replace this process),
//     // we'll just print what would happen
//     printf("This would redirect input from %s and execute %s %s\n\n", 
//            cmd->redirs->fd_file, cmd->args[0], cmd->args[1]);

//     // Test case 2: Create a pipeline
//     printf("=== Test 2: Command pipeline ===\n");
    
//     // First command: ls -l
//     char **args1 = malloc(3 * sizeof(char *));
//     args1[0] = strdup("ls");
//     args1[1] = strdup("-l");
//     args1[2] = NULL;
    
//     t_cmd *cmd1 = new_cmd("ls", args1);
//     cmd1->pipe_out = 1; // This command pipes to the next
    
//     // Second command: grep ".c"
//     char **args2 = malloc(3 * sizeof(char *));
//     args2[0] = strdup("grep");
//     args2[1] = strdup(".c");
//     args2[2] = NULL;
    
//     t_cmd *cmd2 = new_cmd("grep", args2);
//     cmd2->pipe_out = 0; // End of pipeline
    
//     // Link commands
//     cmd1->next = cmd2;
    
//     // Print pipeline info
//     t_cmd *temp = cmd1;
//     int cmd_num = 1;
    
//     while(temp) {
//         printf("Command %d: %s\n", cmd_num, temp->cmd);
//         printf("  Arguments: ");
//         for(int i = 0; temp->args[i]; i++) {
//             printf("%s ", temp->args[i]);
//         }
//         printf("\n");
//         printf("  Pipe out: %d\n", temp->pipe_out);
        
//         temp = temp->next;
//         cmd_num++;
//     }
    
//     // Clean up
//     free_cmd(cmd);
    
//     // Free the pipeline
//     temp = cmd1;
//     while(temp) {
//         t_cmd *next = temp->next;
//         free_cmd(temp);
//         temp = next;
//     }
    
//     return 0;
// }
