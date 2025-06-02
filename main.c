/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:07:21 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/02 15:29:32 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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

int global_sig = 0;
int is_builtin(char **args)
{
	int i = 0;

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
void restory_window(t_cmd *cmd)
{
	dup2(cmd->fd[0], 0);
	dup2(cmd->fd[1], 1);
	close(cmd->fd[0]);
	close(cmd->fd[1]);
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

	// tcgetattr(1, &infos);
	// infos.c_lflag &= ~(ECHOCTL);
	// tcsetattr(1, TCSANOW, &infos); hadi khsha trj3
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

void excute_redrction(t_cmd **cmd, t_env *env_list)
{
		if((*cmd)->redirs)
		{
			if((*cmd)->redirs->fd == -1)
			{
				(*cmd)->data.exit_status = get_or_set(SET, 1);
				restory_window((*cmd));
				return ;
			}
			ft_redircte((*cmd)->redirs, env_list, *cmd);
		}
}

void check_line(t_cmd **command, t_env *env_list, char *env[])
{
	t_cmd	*cmd;
	cmd = *command;

    (*command)->fd[0] = dup(0);
	(*command)->fd[1] = dup(1);
	if ((cmd)->redirs != NULL)
	{
		check_here_doc(*command, env_list);
		// printf("%d\n", cmd->flag);
		if((*command)->flag == 1)
			return ;
	}
	if (cmd->pipe_out)
	{
		ft_excute_mult_pipe(cmd, env_list, env);
		get_or_set(SET, cmd->data.exit_status);
		restory_window(cmd);
		return ;
	}
	else
	{
		excute_redrction(command, env_list);
		execute_single_command(cmd, env_list, env);
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
	puts("MMMM");
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    waitpid(child_pid, &status, 0);
    cmd->data.exit_status = WEXITSTATUS(status);
        if (WIFSIGNALED(status))
        {
                puts("jsjjssjj");
            int sig = WTERMSIG(status);
            if (sig == SIGQUIT)
                ft_putstr_fd("Quit: 3\n", 1);
            else if (sig == SIGINT)
			{
				puts("RRRR");
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
void check_here_doc(t_cmd *cmd, t_env *env)
{
	t_cmd *tmp = cmd;
	t_redir *tmp_redir;
	int *fd;
	int status;
	pid_t pid;

	cmd->flag = 0; // Everything is OK by default

	while (tmp)
	{
		tmp_redir = tmp->redirs;
		while (tmp_redir)
		{
			if (tmp_redir->type == 3) // it's a heredoc
			{
				pid = fork();
				if (pid == 0) // child process
				{
					signal(SIGINT, SIG_DFL); // allow Ctrl+C to work normally
					fd = heredoc(tmp_redir->file, env, 0, tmp_redir->orig_token);
					if (fd != NULL)
					{
						tmp_redir->fd = fd[1];
						close(fd[0]);
						exit(0);
					}
					else
					{
						tmp_redir->fd = -1;
						exit(1);
					}
				}
				else if (pid > 0) // parent process
				{
					waitpid(pid, &status, 0);
					if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
					{
						cmd->flag = 1; // heredoc interrupted
						return;
					}
				}
				else
				{
					perror("fork");
					cmd->flag = 1;
					return;
				}
			}
			tmp_redir = tmp_redir->next;
		}
		tmp = tmp->next;
	}
}

// void check_here_doc(t_cmd *cmd, t_env *env)
// {
// 	t_cmd *tmp;
// 	t_redir *tmp_redir;

// 	tmp_redir = NULL;
// 	tmp = cmd;
// 	int *fd;
// 	cmd->flag = 1;
// 	while (tmp)
// 	{
// 		tmp_redir = tmp->redirs;
// 		while (tmp_redir)
// 		{
// 			pid_t pid;
// 			pid = fork();
// 			if(pid == 0){
// 			if (tmp_redir->type == 3)
// 				{
// 					signal(SIGINT, hb);
// 					fd = heredoc(tmp_redir->file, env, 0, tmp_redir->orig_token);
// 					// printf("%d\n", fd[1]);
// 					if (fd != NULL)
//                 	{
//                     	tmp_redir->fd = fd[1];
//                     	close(fd[0]);
//                 	}
//                 	else
//                 	{
//                     	tmp_redir->fd = -1;
//                 	}
// 				}
// 			}
// 			if(pid > 0)
// 				wait_parent_children(cmd, pid);
// 			else 
// 				perror("fork");
// 			tmp_redir = tmp_redir->next;
// 		}
		
// 		tmp = tmp->next;
// 	}
// }
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
	// tcgetattr(1, &infos);
	while (1)
	{
		desable_echo_term();
		// infos.c_lflag &= ~(ECHOCTL);
		// tcsetattr(1, TCSANOW, &infos);
		signal(SIGINT, handel_signal);
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell $> ");
		if (!input)
		{
			printf("exit\n");
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
		// tcsetattr(1, TCSANOW, &infos);
		free(input);
		free_token_list(token_list);
	}
	// free_env_struct(env_struct);
	return 0;
}
// #include "minishell.h"

// void add_one_shlvl(t_env *env)
// {
//     t_env *tmp = env;
//     int shl_vl = 0;
//     int found = 0;

//     if (!env) 
//         return;
//     while (tmp) 
//     {
//         if (tmp->key && strcmp(tmp->key, "SHLVL") == 0)
//         {
//             found = 1;  // Mark that we found SHLVL
//             if (tmp->value && tmp->value[0] != '\0')
//             {
//                 shl_vl = atoi(tmp->value);
//                 free(tmp->value);
//                 tmp->value = NULL;
//             }
            
//             shl_vl++; 
//             tmp->value = ft_itoa(shl_vl);
//             if (!tmp->value) 
//                 tmp->value = strdup("1");
//             break;
//         }
//         tmp = tmp->next;
//     }
//     if (!found && env)
//     {
//         t_env *new_node = malloc(sizeof(t_env));
//         if (!new_node)
//             return;
            
//         new_node->key = strdup("SHLVL");
//         new_node->value = strdup("1");
//         new_node->is_not_active = 0;
//         new_node->next = NULL;
//         tmp = env;
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = new_node;
//     }
// }

// int global_sig = 0;
// int is_builtin(char **args)
// {
// 	int i = 0;

// 	if(!args || !*args)
// 		return (1);
// 	if (strcmp(args[0], "cd") == 0)
// 		return (0);
// 	else if (strcmp(args[0], "echo") == 0)
// 		return (0);
// 	else if (strcmp(args[0], "unset") == 0)
// 		return (0);
// 	else if (strcmp(args[0], "export") == 0)
// 		return (0);
// 	else if (strcmp(args[0], "pwd") == 0)
// 		return (0);
// 	else if (strcmp(args[0], "env") == 0)
// 		return (0);
// 	else if (strcmp(args[0], "exit") == 0)
// 		return (0);
// 	else
// 		return (1);
// }

// void excute_builting(t_cmd **command, t_env *env_list, char *env[])
// {
// 	t_cmd	*cmd;
// 	int		status;

// 	cmd = *command;
// 	status = 0;

// 	if (strncmp("export", cmd->args[0], 6) == 0 && strlen(cmd->args[0]) == 6)
// 		status = ft_export(cmd->args, &env_list);
// 	else if (strncmp("env", cmd->args[0], 3) == 0 && strlen(cmd->args[0]) == 3)
// 		status = ft_env(*command, env_list);
// 	else if (strncmp("exit", cmd->args[0], 4) == 0 && strlen(cmd->args[0]) == 4)
// 	{
// 		status = ft_exit(cmd->args, cmd->data);
// 		// free_cmd_list(cmd);
// 	}
// 	else if (strncmp("unset", cmd->args[0], 5) == 0 && strlen(cmd->args[0]) == 5)
// 	{
// 		status = ft_unset(&env_list, cmd->args + 1);
// 	}
// 	else if (strncmp("echo", cmd->args[0], 4) == 0 && strlen(cmd->args[0]) == 4)
// 		status = echo(cmd->args);
// 	else if (strncmp("pwd", cmd->args[0], 3) == 0 && strlen(cmd->args[0]) == 3)
// 	{
// 		status = pwd(cmd->data);
// 	}
// 	else if (strncmp("cd", cmd->args[0], 2) == 0 && strlen(cmd->args[0]) == 2)
// 		status = ft_cd(cmd->args, &env_list, cmd->data);
// 	cmd->data.exit_status = get_or_set(SET, status);
// }
// void restory_window(t_cmd *cmd)
// {
// 	dup2(cmd->fd[0], 0);
// 	dup2(cmd->fd[1], 1);
// 	close(cmd->fd[0]);
// 	close(cmd->fd[1]);
// }
// void execute_single_command(t_cmd *cmd, t_env *list_env, char *env[])
// {
		
// 		if(!is_builtin(cmd->args))
// 		{

// 			cmd->data.new_pwd = get_value_env("PWD", &list_env);
// 			excute_builting(&cmd, list_env, env);
// 			get_or_set(SET, cmd->data.exit_status);
// 		}
// 		else
// 		{
// 			ft_excute_commands(cmd, &list_env);
// 			get_or_set(SET, cmd->data.exit_status);	
// 		}
// }
// void handel_signal(int sig)
// {
// 	struct termios infos;

// 	// tcgetattr(1, &infos);
// 	// infos.c_lflag &= ~(ECHOCTL);
// 	// tcsetattr(1, TCSANOW, &infos); hadi khsha trj3
// 	if (sig == SIGINT)
// 	{
// 		global_sig = 2;
// 		ft_putstr_fd("\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// 	else 
// 		global_sig = sig;
// }

// void excute_redrction(t_cmd **cmd, t_env *env_list)
// {
// 		if((*cmd)->redirs)
// 		{
// 			if((*cmd)->redirs->fd == -1)
// 			{
// 				if((*cmd)->redirs->type != 3)
// 					(*cmd)->data.exit_status = get_or_set(SET, 1);
// 				restory_window((*cmd));
// 				return ;
// 			}
// 			ft_redircte((*cmd)->redirs, env_list, *cmd);
// 		}
// }

// void check_line(t_cmd **command, t_env *env_list, char *env[])
// {
// 	t_cmd	*cmd;
// 	cmd = *command;

//     (*command)->fd[0] = dup(0);
// 	(*command)->fd[1] = dup(1);
// 	if ((*command)->redirs != NULL)
// 	{
// 		check_here_doc(*command, env_list);
// 	}
// 	if (cmd->pipe_out)
// 	{
// 		ft_excute_mult_pipe(cmd, env_list, env);
// 		get_or_set(SET, cmd->data.exit_status);
// 		restory_window(cmd);
// 		return ;
// 	}
// 	else
// 	{
// 		excute_redrction(command, env_list);
// 		execute_single_command(cmd, env_list, env);
// 	}
// 	restory_window(cmd);
// }



// void handl_sig_herdoc()
// {
// 	ft_putstr_fd("\n", 1);
// 	exit(1);
// }
// void wait_parent_children(t_cmd *cmd, pid_t child_pid)
// {
//     int status;

//     status = 0;
// 	puts("kkkkkkkk");
//     signal(SIGINT, SIG_IGN);
//     signal(SIGQUIT, SIG_IGN);
//     waitpid(child_pid, &status, 0);
//     cmd->data.exit_status = WEXITSTATUS(status);
//         if (WIFSIGNALED(status))
//         {
//                 puts("jsjjssjj");
//             int sig = WTERMSIG(status);
//             if (sig == SIGQUIT)
//                 ft_putstr_fd("Quit: 3\n", 1);
//             else if (sig == SIGINT)
// 			{
// 				cmd->flag = 1;
//                 cmd->data.exit_status = get_or_set(SET, 1);
// 			}
//             else
//             {
//                 cmd->data.exit_status = get_or_set(SET, 0);
//             }
//         }
// }
// void check_here_doc(t_cmd *cmd, t_env *env)
// {
// 	t_cmd *tmp;
// 	t_redir *tmp_redir;

// 	tmp_redir = NULL;
// 	tmp = cmd;
// 	int *fd;
// 	while (tmp)
// 	{
// 		tmp_redir = tmp->redirs;
// 		while (tmp_redir)
// 		{
// 			pid_t pid;
// 			if(tmp->redirs->type == 3)
// 			{
// 				pid = fork();
// 			if(pid == 0){
// 			if (tmp_redir->type == 3)
// 				{
// 					signal(SIGINT, handl_sig_herdoc);
// 					fd = heredoc(tmp_redir->file, env, 0, tmp_redir->orig_token);
// 					// printf("%d\n", fd[1]);
// 					if (fd != NULL)
//                 	{
//                     	tmp_redir->fd = fd[1];
//                     	close(fd[0]);
//                 	}
//                 	else
//                 	{
//                     	tmp_redir->fd = -1;
//                 	}
// 				}
// 			}
// 			if(pid > 0)
// 				wait_parent_children(cmd, pid);
// 			// else 
// 			// 	perror("fork");
// 			}
// 			tmp_redir = tmp_redir->next;
// 		}
		
// 		tmp = tmp->next;
// 	}
// }
// void check_sig(t_cmd *cmd)
// {
// 	if(global_sig != 0)
// 	{
// 		if (global_sig == 2)
// 		{
// 			global_sig = 1;
// 		}
// 		else
// 		{
// 			global_sig = 0;
// 		}
// 		cmd->data.exit_status = get_or_set(SET, global_sig);
// 	}
// }


// int main(int argc, char *argv[], char *env[])
// {
// 	struct termios infos;
// 	t_token *token_list;
// 	t_env *env_struct = NULL;
// 	char *input;
// 	t_cmd *cmd = NULL;
// 	char *preprocessed_input;

// 	token_list = NULL;
// 	(void)argc;
// 	(void)argv;
// 	env_struct = env_maker(env, &env_struct);
// 	if (!env_struct)
// 		env_null(&env_struct);
// 	if(!isatty(1))
// 	{
// 		exit(1);
// 	}
// 	tcgetattr(1, &infos);
// 	while (1)
// 	{
// 		infos.c_lflag &= ~(ECHOCTL);
// 		tcsetattr(1, TCSANOW, &infos);
// 		signal(SIGINT, handel_signal);
// 		signal(SIGQUIT, SIG_IGN);
// 		input = readline("minishell $> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		if (global_sig == 2 && input[0] == '\0')
// 		{
// 			global_sig = 0;
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
// 		if (!preprocessed_input)
// 		{
// 			free(input);
// 			continue;
// 		}

// 		token_list = tokin_list_maker(preprocessed_input);
// 		if (token_list && !error_pipi(token_list) && !check_syntax_errors(token_list))
// 		{
// 			cmd = parser(token_list);
// 			check_sig(cmd);
// 			expand_handle(cmd, env_struct, get_or_set(GET, 0));
// 			ambiguous_finder(cmd);
// 			process_quotes_for_cmd(cmd, 1);
// 			file_opener(cmd, env_struct);
// 			check_line(&cmd, env_struct, env);
// 			expand_handle(cmd, env_struct, cmd->data.exit_status);
// 			global_sig = 0;
// 		}
// 		free(input);
// 		free_token_list(token_list);
// 	}
// 	tcsetattr(1, TCSANOW, &infos);
// 	// free_env_struct(env_struct);
// 	return 0;
// }
