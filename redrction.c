/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redrction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 17:59:21 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/01 16:22:21 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_redircte(t_redir *rederction, t_env *env, t_cmd *cmd)
{
    t_redir *tmp;

    tmp = rederction;

    while(tmp)
    {
                    printf("fd_name = %s\n and amb= %d\n", tmp -> file, tmp->Ambiguous);
        if(tmp->type == 0) 
        {
            dup2(tmp->fd, 0);
            close(tmp->fd); 
        }
        else if (tmp->type == 1) 
        {
            // printf("-> %d \n", tmp->fd);
            dup2(tmp->fd, 1);
            close(tmp->fd);
        }
        else if(tmp->type == 2 )
        {
            dup2(tmp->fd, 1);
            close (tmp->fd);
        }
        tmp = tmp->next;
    }
}

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