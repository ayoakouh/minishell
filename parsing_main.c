#include "minishell.h"


void ff()
{
    system("leaks minishell");
}

int main(int argc, char *argv[], char *env[])
{
    t_token *token_list;
    t_env *env_struct = NULL;   //// add to the final main
    int exit_status;
    char *input;
    t_cmd *cmd;
    
    (void)argc;
    (void)argv;
    atexit(ff);
    env_struct=env_maker(env, &env_struct);
    token_list = NULL;
    while (1)
    {
        input = readline("minishell $> ");
        if (!input)
            break;
        add_history(input);
        cmd = NULL;
        if (check_quotes(input))
        {
            // Error message already printed by check_quotes
            free(input);
            continue;
        }
            
        token_list = tokin_list_maker(input);
        if (token_list && !error_pipi(token_list)  && !check_syntax_errors(token_list))
        {
            printf("--- TOKENS ---\n");
            expand_handle(token_list, env_struct, exit_status);
            //process_quotes_for_tokens(token_list, 1);
            cmd = parser(token_list);
            check_line(&cmd, env_struct, env);
            //debug_print_cmd(cmd);
            if (cmd == NULL) {
                printf("Warning: Command list is empty after parsing!\n");
            } else {
                process_quotes_for_cmd(cmd, 1);
                // print_cmd(cmd);
                if (cmd)
                    free_cmd_list(cmd);
            }
        }   
        free_token_list(token_list);
        
        free(input);
    }
    free_env_struct(env_struct);
    return 0;
}
