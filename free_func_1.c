#include "minishell.h"

void free_redirs_list(t_redir *redir_list)
{
    t_redir *current;
    t_redir *next;

    current = redir_list;

    while (current)
    {
        next = current->next;
        free(current->file);
        free(current);
        current = next;
    }
}

void free_cmd_list(t_cmd *cmd_list)
{
    t_cmd *current;
    t_cmd *next;
    int i;

    i = 0;
    current = cmd_list;
    while (current)
    {
        next = current->next;
        free(current->cmd); // Free the separate command name
        // Free args, redirs, etc.
        while (current->args[i])
            free(current->args[i++]);
        free(current->args);
        free_redirs_list(current->redirs);
        free(current);
        current = next;
    }
}