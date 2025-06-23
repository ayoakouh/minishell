/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:35:13 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 17:24:45 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void split_stoper(t_cmd *cmd)
// {
//     t_cmd *tmp;
//     char *new_str;
//     int exp = 0;
    
//     if (!cmd)
//         return;
        
//     tmp = cmd;
//     while(tmp)
//     {
//         int i = 0;
//         exp = 0; 
        
//         while (tmp->args && tmp->args[i])
//         {
//             if (i == 0 && tmp->args[i] && strcmp(tmp->args[i], "export") == 0) 
//                 exp = 1;
//             if (tmp->args_befor_quotes_remover && tmp->args_befor_quotes_remover[i])
//             {
//                 new_str = split_helper(tmp->args[i], tmp->args_befor_quotes_remover[i], exp);
//                 if (new_str != NULL)
//                 {
//                     free(tmp->args[i]);
//                     tmp->args[i] = new_str;
//                 }
//             }
//             i++;
//         }
//         tmp = tmp->next;
//     }
// }


// char *chenger_back(char *str)
// {
//     int i = 0;

//     while (str && str[i])
//     {
//         if (str[i] == 3)
//             str[i] = '\'';
//         else if (str[i] == 4)
//             str[i] = '\"';
//         i++;
//     }
//     return str;
// }

// void change_back_cmd(t_cmd *cmd)
// {
//     t_cmd *tmp;
//     int i = 0;
//     tmp = cmd;

//     while (tmp)
//     {
//         i = 0;
//         while (tmp->args[i])
//         {
//             tmp->args[i] = chenger_back(tmp->args[i]);
//             i++;
//         }
//         tmp->cmd = chenger_back(tmp->cmd);
//         i = 0;
//         t_redir *tp = tmp->redirs;
//         while (tp)
//         {
//             tp->file = chenger_back(tp->file);
//             tp = tp->next;
//         }
//         tmp = tmp->next;
//     }
// }
// char *change_space(char *str)
// {
//     int i = 0;
//     int quote_state = 0;
    
//     while(str && str[i])
//     {
//         if (str[i] == '\'')
//         {
//             if (quote_state == 0)
//                 quote_state = 1;
//             else if (quote_state == 1)
//                 quote_state = 0;
//         }
//         else if (str[i] == '"')
//         {
//             if (quote_state == 0)
//                 quote_state = 2;
//             else if (quote_state == 2)
//                 quote_state = 0;
//         }
//         if (str[i] >= 9 && str[i] <=13 && quote_state == 0)
//             str[i] = ' ';
//         i++;
//     }
//     return str;
// }
// void free_extract_result(char **split)
// {
//     if (!split)
//         return;
    
//     if (split[0])
//         free(split[0]);
//     if (split[1])
//         free(split[1]);
//     free(split);
// }

// char **extract(char *str)
// { 
//     int i = 0;
//     char *key;
//     char *value;
//     char **split = malloc(sizeof(char *) * 3);
    
//     if (!split)
//         return NULL;
//     while (str && str[i] && str[i] != '=')
//         i++;
//     key = ft_substr(str, 0, i);
//     if (!key) 
//     {
//         free(split);
//         return NULL;
//     }
//     value = ft_substr(str, i+1, ft_strlen(str) - (i+1));
//     if (!value) 
//     {
//         free(key);
//         free(split);
//         return NULL;
//     }
//     split[0] = key;
//     split[1] = value;
//     split[2] = NULL;
    
//     return split;
// }
// char *plus_checker(char *str)
// {
//     int i = 0;
    
//     if (!str)
//         return str;
        
//     while (str[i])
//         i++;
        
//     if (i > 0 && str[i - 1] == '+')
//         str[i - 1] = '\0';
//     return str;
// }


// char *split_helper(char *str, char *befor, int exp)
// {
//     char **split;
//     char *join1 = NULL;
//     char *join3 = NULL;
//     char *join4 = NULL;
//     char *join2 = NULL;
//     char *new_key = NULL;
    
//     if (exp != 1)
//         return NULL;
        
//     if (strchr(str, '=') != NULL)
//     {
//         split = extract(str);
//         if (split != NULL)
//         {
//             new_key = ft_strdup(split[0]);
//             if (!new_key)
//             {
//                 free_extract_result(split);
//                 return NULL;
//             }
            
//             new_key = plus_checker(new_key);
//             if ((((strchr(split[0], '\'') == NULL && strchr(split[0], '\"') == NULL) && 
//                  strchr(split[0], '$') == NULL)) && is_valid_key(new_key) == 0)
//             {
//                 if (split && split[1] && strchr(split[1], '$') != NULL)
//                 {
//                     join1 = ft_strjoin("\"", split[1]);
//                     if (!join1) 
//                     {
//                         free(new_key);
//                         free_extract_result(split);
//                         return NULL;
//                     }
//                     join2 = ft_strjoin(join1, "\"");
//                     if (!join2) 
//                     {
//                         free(join1);
//                         free(new_key);
//                         free_extract_result(split);
//                         return NULL;
//                     }
//                     join3 = ft_strjoin("=", join2);
//                     if (!join3) 
//                     {
//                         free(join1);
//                         free(join2);
//                         free(new_key);
//                         free_extract_result(split);
//                         return NULL;
//                     }
//                     join4 = ft_strjoin(split[0], join3);
//                     if (!join4)
//                     {
//                         free(join1);
//                         free(join2);
//                         free(join3);
//                         free(new_key);
//                         free_extract_result(split);
//                         return NULL;
//                     }
//                     free(join1);
//                     free(join2);
//                     free(join3);
//                 }
//                 else
//                 {
//                     join3 = ft_strjoin(split[0], "=");
//                     if (!join3) 
//                     {
//                         free(new_key);
//                         free_extract_result(split);
//                         return NULL;
//                     }
//                     join4 = ft_strjoin(join3, split[1]);
//                     if (!join4)
//                     {
//                         free(join3);
//                         free(new_key);
//                         free_extract_result(split);
//                         return NULL;
//                     }
//                     free(join3);
//                 }
//             }
//             else
//             {
//                 join4 = ft_strdup(str);
//                 if (!join4)
//                 {
//                     free(new_key);
//                     free_extract_result(split);
//                     return NULL;
//                 }
//             }
//             free(new_key); 
//             free_extract_result(split);
//         }
//         else
//         {
//             join4 = ft_strdup(str);
//             if (!join4)
//                 return NULL;
//         }
//     }
//     else
//     {
//         join4 = ft_strdup(str);
//         if (!join4)
//             return NULL;
//     }
//     return join4;    
// }

// void add_one_shlvl(t_env *env)
// {
// 	t_env *tmp = env;
// 	int shl_vl = 0;
// 	int found = 0;

// 	if (!env) 
// 		return;
// 	while (tmp) 
// 	{
// 		if (tmp->key && strcmp(tmp->key, "SHLVL") == 0)
// 		{
// 			found = 1;
// 			if (tmp->value && tmp->value[0] != '\0')
// 			{
// 				shl_vl = atoi(tmp->value);
// 				free(tmp->value);
// 				tmp->value = NULL;
// 			}
			
// 			shl_vl++; 
// 			tmp->value = ft_itoa(shl_vl);
// 			if (!tmp->value) 
// 				tmp->value = strdup("1");
// 			break;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (!found && env)
// 	{
// 		t_env *new_node = malloc(sizeof(t_env));
// 		if (!new_node)
// 			return;
			
// 		new_node->key = strdup("SHLVL");
// 		new_node->value = strdup("1");
// 		new_node->is_not_active = 0;
// 		new_node->next = NULL;
// 		tmp = env;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_node;
// 	}
// }

int global_sig = 0;
int is_builtin(char **args)
{
	if(!args || !*args)
		return (1);
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

void excute_builting(t_cmd **command, t_env **env_list, char *env[])
{
	t_cmd	*cmd;
	int		status;

	cmd = *command;
	status = 0;

	if (strncmp("export", cmd->args[0], 6) == 0)
	{
		status = ft_export(cmd->args, env_list);
	}
	else if (strncmp("env", cmd->args[0], 3) == 0)
	{
		status = ft_env(*command, *env_list);
	}
	else if (strncmp("exit", cmd->args[0], 4) == 0)
	{
		status = ft_exit(cmd->args, cmd->data);
	}
	else if (strncmp("unset", cmd->args[0], 5) == 0)
	{
		status = ft_unset(env_list, cmd->args + 1);
	}
	else if (strncmp("echo", cmd->args[0], 4) == 0)
		status = echo(cmd->args);
	else if (strncmp("pwd", cmd->args[0], 3) == 0)
	{
		status = pwd(cmd);
	}
	else if (strncmp("cd", cmd->args[0], 2) == 0)
		status = ft_cd(cmd->args, env_list, cmd);
	// puts("kkkkk");
	// t_env *tmp = env_list;
	// while(tmp)
	// {
	//     printf("%s,,, %s\n", tmp->key, tmp->value);
	//     tmp = tmp ->next;
	// }
	cmd->data.exit_status = get_or_set(SET, status);
}
void restory_window(t_cmd *cmd)
{
	dup2(cmd->fd[0], 0);
	dup2(cmd->fd[1], 1);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
}
void execute_single_command(t_cmd *cmd, t_env **list_env, char *env[], int flag)
{
		if(!is_builtin(cmd->args))
		{
			excute_builting(&cmd, list_env, env);
			get_or_set(SET, cmd->data.exit_status);
		}
		else
		{
			ft_excute_commands(cmd, list_env, flag);
			get_or_set(SET, cmd->data.exit_status);	
		}
}
void handel_signal(int sig)
{
	if (sig == SIGINT)
	{
		get_or_set(SET, 1);
		global_sig = 2;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else 
		global_sig = sig;
		

}

int excute_redrction(t_cmd **cmd, t_env *env_list)
{
	if((*cmd)->redirs)
	{
		if((*cmd)->redirs->fd[0] == -1)
		{
			(*cmd)->data.exit_status = get_or_set(SET, 1);
			restory_window((*cmd));
			return(-1) ;
		}
		ft_redircte((*cmd)->redirs);
	}
	return (0);
}
void cleanup_all_heredocs(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	t_redir *tmp_redir;
	
	while (tmp)
	{
		tmp_redir = tmp->redirs;
		while (tmp_redir)
		{
			if (tmp_redir->type == 3)
			{
				close_heredoc_fds(tmp_redir);
			}
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
}
void check_line(t_cmd **command, t_env **env_list, char *env[])
{
	t_cmd	*cmd;
	cmd = *command;
	// int flag = 0;
	(*command)->fd[0] = dup(0);
	(*command)->fd[1] = dup(1);
    if ((*command)->redirs != NULL)
    {
        check_here_doc(*command, *env_list);
        if ((*command)->flag == 1)
        {
			cleanup_all_heredocs(cmd);
            restory_window(*command);
            return;
        }
    }
	if (cmd->pipe_out)
	{
		ft_excute_mult_pipe(cmd, *env_list, env);
		cleanup_all_heredocs(cmd);
		get_or_set(SET, cmd->data.exit_status);
		restory_window(cmd);
		return ;
	}
	else
	{
		if(excute_redrction(command, *env_list) == -1)
		{
			restory_window(cmd);
			return ;
		}
		execute_single_command(*command, env_list, env, 1);	
	}
	restory_window(cmd);
}

void handl_sig_herdoc()
{
	ft_putstr_fd("\n", 1);
	exit(12);
}
void wait_parent_children(t_cmd *cmd, pid_t child_pid)
{
	int status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(child_pid, &status, 0);
	cmd->data.exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGQUIT)
				ft_putstr_fd("Quit: 3\n", 1);
			else if (sig == SIGINT)
			{
				cmd->flag = 1;
				cmd->data.exit_status = get_or_set(SET, 1);
			}
			else
			{
				cmd->data.exit_status = get_or_set(SET, 0);
			}
		}
}
void hb(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void check_sig(t_cmd **cmd)
{
	if (cmd == NULL|| *cmd == NULL)
		return ;
	// if(global_sig != 0)
	// {
	// 	if (global_sig == 2)
	// 	{
	// 		get_or_set(SET, 1);
	// 		// global_sig = 1;
	// 	}
	// 	else
	// 	{
	// 		// global_sig = 0;
	// 		 get_or_set(SET, 0);
	// 	}
	// }
}


void check_set(t_env **env)
{
	t_env *tmp = *env;
	int path;
	int oldpwd;
	int pwd;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
			path = 1;
		else if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			oldpwd = 1;
		else if (ft_strcmp(tmp->key, "PWD") == 0)
			pwd = 1;
		tmp = tmp->next;
	}
	
	if (path != 1)
		ft_lstadd_back_env(env, creat_new_env(ft_strdup("PATH"), ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
	if (oldpwd != 1)
		ft_lstadd_back_env(env, creat_new_env(ft_strdup("OLDPWD"), NULL));
	if (pwd != 1)
		ft_lstadd_back_env(env, creat_new_env(ft_strdup("PWD"), getcwd(NULL, 0)));

}

//------------main--------------//
void shell_mode(void)
{
	if(!isatty(1) || !isatty(0) || !getcwd(NULL, 0))
		exit(1);
}

t_shell_var *init_shell(char **env)
{
    t_shell_var *var;
    
    var = malloc(sizeof(t_shell_var));
    if (!var)
        return (NULL);
	var->env_struct = NULL;
    var->env_struct = env_maker(env, &var->env_struct);
    check_set(&var->env_struct);
    var->env = env;
    var->exit_status = 0;
    add_one_shlvl(var->env_struct);
    tcgetattr(1, &var->infos);
    return (var);
}

void setup_signals_and_terminal(void)
{
    desable_echo_term();
    signal(SIGINT, handel_signal);
    signal(SIGQUIT, SIG_IGN);
}

// char *get_user_input(t_cmd *cmd)
// {
//     char *input;
    
//     input = readline("minishell $> ");
//     if (!input)
//     {
//         printf("exit\n");
//         if (!cmd || !cmd->data.exit_status)
//             exit(0);
//         exit(cmd->data.exit_status);
//     }
//     add_history(input);
//     return input;
// }

char *process_input(char *input, int *should_continue)
{
    char *preprocessed_input;
    
    if (check_quotes(input))
    {
        get_or_set(SET, 258);
        free(input);
        *should_continue = 1;
        return (NULL);
    }
    preprocessed_input = preprocess_command(input);
    if (!preprocessed_input)
    {
        free(input);
        *should_continue = 1;
        return (NULL);
    }
    free(input);
    *should_continue = 0;
    return (preprocessed_input);
}


t_token *create_token_list(char *preprocessed_input)
{
    char *new_input;
    t_token *token_list;
    
    new_input = change_space(preprocessed_input);
    token_list = tokin_list_maker(new_input);
    free(preprocessed_input);
    return (token_list);
}

void run_exuc(t_token *token_list, t_shell_var *state, int *status)
{
    t_cmd *cmd;
    
    cmd = parser(token_list);
    split_stoper(cmd);
    free_token_list(token_list);
    //check_sig(cmd);
    expand_handle(cmd, state->env_struct, get_or_set(GET, 0));
    ambiguous_finder(cmd);
    process_quotes_for_cmd(cmd, 1);
    change_back_cmd(cmd);
    file_opener(cmd, state->env_struct);
    print_ambiguous_redir_errors(cmd);
    check_line(&cmd, &state->env_struct, state->env);
    *status = cmd->data.exit_status;
    free_cmd_list(cmd);
    global_sig = 0;
}


void process_tokens(t_token *token_list,  t_shell_var *state, int *status)
{
    int has_pipe_error;
    int has_syntax_error;
    
    if (!token_list)
        return;
    
    has_pipe_error = error_pipi(token_list);
    has_syntax_error = check_syntax_errors(token_list);
    
    if (!has_pipe_error && !has_syntax_error)
        run_exuc(token_list, state, status);
    else if (has_pipe_error || has_syntax_error)
    {
        get_or_set(SET, 258);
        free_token_list(token_list);
    }
    else
        free_token_list(token_list);
}


void minishell_loop(t_shell_var *state, int *status)
{
    char *input;
    char *preprocessed_input;
    t_token *token_list;
    int should_continue;
    t_cmd *cmd = NULL;
    
    while (1)
    {
        setup_signals_and_terminal();
        input = readline("minishell $> ");
        if (!input)
        {
            printf("exit\n");
            if(global_sig == 2)
                *status = 1;
            break;
        }
        add_history(input);
        preprocessed_input = process_input(input, &should_continue);
        if (should_continue)
            continue;
        token_list = create_token_list(preprocessed_input);
        process_tokens(token_list, state, status);
        tcsetattr(1, TCSANOW, &state->infos);
    }
}


void cleanup_minishell(t_shell_var *state)
{
    if (state)
    {
        free_env_struct(state->env_struct);
        free(state);
    }
}

int main(int argc, char *argv[], char *env[])
{
    t_shell_var *var;
    int status = 0;
    
    (void)argc;
    (void)argv;
    shell_mode();
    var = init_shell(env);
    if (!var)
        return (1);
    minishell_loop(var, &status);
    cleanup_minishell(var);
    exit(status);
    return (0);
}


// int main(int argc, char *argv[], char *env[])
// {
// 	struct termios infos;
// 	t_token *token_list;
// 	t_env *env_struct = NULL;
// 	char *input;
// 	t_cmd *cmd = NULL;
// 	char *preprocessed_input;
// 	int exit_status;
// 	int status = 0;
// 	char **env_doble;

// 	token_list = NULL;
// 	(void)argc;
// 	(void)argv;
// 	env_struct = env_maker(env, &env_struct);
// 	check_set(&env_struct);
// 	// env_doble = convert_env_list(&env_struct);
// 	if(!isatty(1) || !isatty(0) || !getcwd(NULL, 0))
// 	{
// 		exit(1);
// 	}
// 	add_one_shlvl(env_struct);
// 	tcgetattr(1, &infos);
// 	while (1)
// 	{
// 		desable_echo_term();
// 		signal(SIGINT, handel_signal);
// 		signal(SIGQUIT, SIG_IGN);
// 		input = readline("minishell $> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			if(global_sig == 2)
// 				status = 1;
// 			break ;
// 			// exit(get_or_set(GET, 0)) ;
// 		}
// 		// if (global_sig == 2 && input[0] == '\0')
// 		// {
// 		// 	global_sig = 0;
// 		// 	free(input);
// 		// 	continue;
// 		// 	puts("lll");
// 		// }
// 		add_history(input);
// 		if (check_quotes(input))
// 		{
// 			exit_status = get_or_set(SET, 258);
// 			free(input);
// 			continue;
// 		}
// 		preprocessed_input = preprocess_command(input);
// 		free(input);
// 		if (!preprocessed_input)
// 		{
// 			free(input);
// 			continue;
// 		}
// 		char *new_input = change_space(preprocessed_input); 
// 		token_list = tokin_list_maker(new_input);
// 		free(preprocessed_input);
// 		if (token_list && !error_pipi(token_list) && !check_syntax_errors(token_list))
// 		{
// 			cmd = parser(token_list);
// 			split_stoper(cmd);
// 			free_token_list(token_list);
// 			check_sig(&cmd);
// 			expand_handle(cmd, env_struct, get_or_set(GET, 0));
// 			ambiguous_finder(cmd);
// 			process_quotes_for_cmd(cmd, 1);
// 			change_back_cmd(cmd);
// 			file_opener(cmd, env_struct);
// 			print_ambiguous_redir_errors(cmd);
// 			check_line(&cmd, &env_struct, env);
// 			status = cmd->data.exit_status;
// 			free_cmd_list(cmd);
// 			global_sig = 0;
// 		}
// 		else if (error_pipi(token_list)  || check_syntax_errors(token_list))/// must stay
// 			exit_status = get_or_set(SET, 258); /// must stay
// 		else if (token_list)/// must stay
// 		{
// 			free_token_list(token_list);/// must stay
// 		}
// 		tcsetattr(1, TCSANOW, &infos);
// 		// free(input);
// 		// free_token_list(token_list);
// 	}
// 	free_env_struct(env_struct);
// 		exit(status); 
// 	return 0;
// }