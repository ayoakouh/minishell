#include "parsing.h"

void	print_tokens(t_token *token_list)
{
	t_token	*current;
	int		i;

	current = token_list;
	i = 0;
	while (current)
	{
		printf("Token %d: DATA=[%s], TYPE=[%s]\n",
			i++, current->DATA, current->TOKIN);
		current = current->next;
	}
}

void	print_env(t_env *env_struct)
{
	t_env *tmp;

	tmp = env_struct;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}

}


void print_cmd(t_cmd *cmd_list)
{
    t_cmd *tmp;
    int i = 0;
    int j = 0;
    tmp = cmd_list;

    while (tmp)
    {
        i = 0;
        j = 0;  // Reset j for each command
        
        // Check if cmd is NULL before printing
        if (tmp->cmd)
            printf("command name : %s\n", tmp->cmd);
        else
            printf("command name : (null)\n");
            
        // Check if args is NULL before accessing
        if (tmp->args) {
            while (tmp->args[i])
            {
                printf("command args : %s\n", tmp->args[i]);
                i++;
            }
        }
        
        // Check if args_befor_quotes_remover is NULL before accessing
        if (tmp->args_befor_quotes_remover) {
            while (tmp->args_befor_quotes_remover[j])
            {
                printf("args befor quotes remover : %s\n", tmp->args_befor_quotes_remover[j]);
                j++;
            }
        }
        
        if (tmp->redirs)
        {
            t_redir *tp = tmp->redirs;
            printf("redir list\n");
            printf("0:<, 1:>, 2:>>, 3:<< \n");
            while (tp)
            {
                printf("type of redir : %d\n", tp->type);
                
                // Check if orig_token is NULL before printing
                if (tp->orig_token)
                    printf("file name befor the expanend : %s\n", tp->orig_token);
                else
                    printf("file name befor the expanend : (null)\n");
                    
                // Check if file is NULL before printing
                if (tp->file)
                    printf("file name : %s\n", tp->file);
                else
                    printf("file name : (null)\n");
                    
                printf("fd for the file : %d\n", tp->fd);
                printf("ambiguous %d\n", tp->Ambiguous);
                tp = tp->next;
            }
        }
        printf("is there any pipe ? : %d\n", tmp->pipe_out);
        printf("\n");
        tmp = tmp->next;
    }   
}

void print_ambiguous_redir_errors(t_cmd *cmd)
{
    t_cmd *tmp;
    t_redir *redir;
    char *prefix = "minishell: ";
    char *suffix = ": ambiguous redirect\n";
    char *error_msg;

    tmp = cmd;
    while (tmp)
    {
        redir = tmp->redirs;
        while (redir)
        {
            if (redir->Ambiguous)
            {
                write(2, prefix, ft_strlen(prefix));
                if (redir->orig_token)
                    write(2, redir->orig_token, ft_strlen(redir->orig_token));
                else
                    write(2, "$EMPTY", 6);
                write(2, suffix, ft_strlen(suffix));
            }
            redir = redir->next;
        }
        tmp = tmp->next;
    }
}
