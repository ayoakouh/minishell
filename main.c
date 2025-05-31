/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:07:21 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/05/30 16:53:18 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
// int get_or_set(int type, int status)
// {
// 	static int exit_status = 0;

// 	if (type == SET)
// 		exit_status = status; // rje3 dkre hadik kifch dkhlha m3a exit_status;
// 	return (exit_status); // always return the current value
// }
void excute_builting(t_cmd **command, t_env *env_list, char *env[])
{
	t_cmd	*cmd;
	int		status;

	cmd = *command;
	status = 0;

	if (strncmp("export", cmd->args[0], 6) == 0 && strlen(cmd->args[0]) == 6)
		status = ft_export(cmd->args, &env_list);
	else if (strncmp("env", cmd->args[0], 3) == 0 && strlen(cmd->args[0]) == 3)
		status = ft_env(*command, env_list);
	else if (strncmp("exit", cmd->args[0], 4) == 0 && strlen(cmd->args[0]) == 4)
	{
		status = ft_exit(cmd->args, cmd->data);
		// free_cmd_list(cmd);
	}
	else if (strncmp("unset", cmd->args[0], 5) == 0 && strlen(cmd->args[0]) == 5)
	{
		status = ft_unset(&env_list, cmd->args + 1);
	}
	else if (strncmp("echo", cmd->args[0], 4) == 0 && strlen(cmd->args[0]) == 4)
		status = echo(cmd->args);
	else if (strncmp("pwd", cmd->args[0], 3) == 0 && strlen(cmd->args[0]) == 3)
	{
		status = pwd(cmd->data);
	}
	else if (strncmp("cd", cmd->args[0], 2) == 0 && strlen(cmd->args[0]) == 2)
		status = ft_cd(cmd->args, &env_list, cmd->data);
	cmd->data.exit_status = get_or_set(SET, status);
}
void execute_single_command(t_cmd *cmd, t_env *list_env, char *env[])
{
		if(!is_builtin(cmd->args))
		{
			cmd->data.new_pwd = get_value_env("PWD", &list_env);
			excute_builting(&cmd, list_env, env);
			get_or_set(SET, cmd->data.exit_status);
		}
		else
		{
			ft_excute_commands(cmd, &list_env);
			get_or_set(SET, cmd->data.exit_status);
		}
}
void handel_signal(int sig)
{
	struct termios infos;

	tcgetattr(1, &infos);
	infos.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, TCSANOW, &infos);
	if (sig == SIGINT)
	{
		global_sig = 2;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else 
		global_sig = sig;
}
void check_line(t_cmd **command, t_env *env_list, char *env[])
{
	t_cmd	*cmd;
	cmd = *command;
	int fd_input ;
	int fd_output ;

	if ((*command)->redirs != NULL)
		check_here_doc(*command, env_list);
    fd_input = dup(0);
	fd_output = dup(1);
	if (cmd->pipe_out)
	{
		dup2(fd_input, 0);
		dup2(fd_output, 1);
		close(fd_input);
		close(fd_output);
		ft_excute_mult_pipe(cmd, env_list, env);
		get_or_set(SET, cmd->data.exit_status);
		return ;
	}
	else
	{
		if(cmd->redirs)
		{
			if(cmd->redirs->fd == -1)
			{
					dup2(fd_input, 0);
					dup2(fd_output, 1);
					close(fd_input);
					close(fd_output);
					cmd->data.exit_status = get_or_set(SET, 1);
					return ;
			}
			ft_redircte(cmd->redirs, env_list, *command);
			execute_single_command(cmd, env_list, env);
		}
		else
			execute_single_command(cmd, env_list, env);
	}
	dup2(fd_input, 0);
	dup2(fd_output, 1);
	close(fd_input);
	close(fd_output);
}



void add_one_shlvl(t_env *env)
{
    t_env *tmp = env;
    int shl_vl = 0;
    int found = 0;

    if (!env) 
        return;
    while (tmp) 
    {
        if (tmp->key && strcmp(tmp->key, "SHLVL") == 0)
        {
            found = 1;  // Mark that we found SHLVL
            if (tmp->value && tmp->value[0] != '\0')
            {
                shl_vl = atoi(tmp->value);
                free(tmp->value);
                tmp->value = NULL;
            }
            
            shl_vl++; 
            tmp->value = ft_itoa(shl_vl);
            if (!tmp->value) 
                tmp->value = strdup("1");
            break;
        }
        tmp = tmp->next;
    }
    if (!found && env)
    {
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node)
            return;
            
        new_node->key = strdup("SHLVL");
        new_node->value = strdup("1");
        new_node->is_not_active = 0;
        new_node->next = NULL;
        tmp = env;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}

void check_here_doc(t_cmd *cmd, t_env *env)
{
	 /* 0:<, 1:>, 2:>>, 3:<< */
	t_cmd *tmp;
	t_redir *tmp_redir;
	tmp_redir = NULL;
	tmp = cmd;
	int *fd;
	while (tmp)
	{
		tmp_redir = tmp->redirs;
		while (tmp_redir)
		{
			if (tmp_redir->type == 3)
				{
					fd = heredoc(tmp_redir->file, env, 0, tmp_redir->orig_token);
					// printf("%d\n", fd[1]);
					if (fd != NULL)
                	{
                    	tmp_redir->fd = fd[1];
                    	close(fd[0]);
                	}
                	else
                	{
                    tmp_redir->fd = -1;
                }
				}
			tmp_redir = tmp_redir->next;
		}
		
		tmp = tmp->next;
	}
}
void check_sig(t_cmd *cmd)
{
	if(global_sig != 0)
	{
		if (global_sig == 2)
		{
			global_sig = 1;
		}
		else
		{
			global_sig = 0;
		}
		cmd->data.exit_status = get_or_set(SET, global_sig);
	}
}


int main(int argc, char *argv[], char *env[])
{
	struct termios infos;
	t_token *token_list;
	t_env *env_struct = NULL;
	char *input;
	t_cmd *cmd = NULL;
	char *preprocessed_input;

	token_list = NULL;
	(void)argc;
	(void)argv;
	env_struct = env_maker(env, &env_struct);
	if (!env_struct)
		env_null(&env_struct);
	if(!isatty(1))
	{
		exit(1);
	}
	tcgetattr(1, &infos);
	while (1)
	{
		infos.c_lflag &= ~(ECHOCTL);
		tcsetattr(1, TCSANOW, &infos);
		signal(SIGINT, handel_signal);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell $> ");
		if (!input)
		{
			printf("exit");
			break ;
		}
		if (global_sig == 2 && input[0] == '\0')
		{
			global_sig = 0;
			free(input);
			continue;
		}
		add_history(input);

		if (check_quotes(input))
		{
			free(input);
			continue;
		}

		preprocessed_input = preprocess_command(input); 
		if (!preprocessed_input)
		{
			free(input);
			continue;
		}

		token_list = tokin_list_maker(preprocessed_input);
		if (token_list && !error_pipi(token_list) && !check_syntax_errors(token_list))
		{
			cmd = parser(token_list);
			check_sig(cmd);
			expand_handle(cmd, env_struct, get_or_set(GET, 0));
			ambiguous_finder(cmd);
			process_quotes_for_cmd(cmd, 1);
			file_opener(cmd, env_struct);
			check_line(&cmd, env_struct, env);
			expand_handle(cmd, env_struct, cmd->data.exit_status);
			global_sig = 0;
		}
		free(input);
		free_token_list(token_list);
	}
	tcsetattr(1, TCSANOW, &infos);
	free_env_struct(env_struct);
	return 0;
}

// int main(int argc, char *argv[], char *env[])
// {
// 	t_token *token_list;
// 	t_env *env_struct = NULL;
// 	char *input;
// 	t_cmd *cmd = NULL;
// 	// cmd->data.exit_status = 0;
// 	char *preprocessed_input;
// 		struct termios infos;

// 	(void)argc;
// 	(void)argv;
// 		puts("kkk");
// 	// if(!isatty(1))
// 	// {
// 	// 	exit(1);
// 	// }
// 	env_struct = env_maker(env, &env_struct);
// 	if(!env_struct)
// 		env_null(&env_struct);
// 	token_list = NULL;
// 	// tcgetattr(1, &infos);
// 		// infos.c_lflag &= ~(ECHOCTL);
// 		signal(SIGINT, handel_signal);
// 		signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		input = readline("minishell $> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		printf("%d\n", global_sig);
// 		if(global_sig != 0)
// 		{
// 			free(input);
// 			continue;
// 		}
// 		add_history(input);
// 		if (check_quotes(input))
// 		{
// 			free(input);
// 			continue;
// 		}
// 		preprocessed_input = preprocess_command(input); 
//          if (!preprocessed_input)
//             continue;
// 		token_list = tokin_list_maker(preprocessed_input);
// 		if (token_list && !error_pipi(token_list)  && !check_syntax_errors(token_list))
// 		{
// 			cmd = parser(token_list);
// 			expand_handle(cmd, env_struct, get_or_set(GET, 0));
// 			ambiguous_finder(cmd);
// 			process_quotes_for_cmd(cmd, 1);
// 			file_opener(cmd, env_struct);
// 			// print_cmd(cmd);
// 			check_line(&cmd, env_struct, env);
// 			check_sig(cmd);
// 			expand_handle(cmd, env_struct, cmd->data.exit_status);
// 			// free_cmd_list(cmd);
// 			global_sig = 0;
// 			free(input);
// 		}
// 		// free_cmd_list(cmd);
// 		free_token_list(token_list);
// 	}
// 		// tcsetattr(1, TCSANOW, &infos);
// 	free_env_struct(env_struct);
// 	return 0;
// }