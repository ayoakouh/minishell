/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:41:00 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/05/01 20:19:54 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_check_rederction(t_redir *cmd)
// {
//     t_redir *tmp;

//     tmp = cmd;
//     // while(tmp)
//     // {
//         if(tmp->redirs != NULL)
//         {
//             ft_redircte(&cmd);
//             return (0);
//         }
//         // tmp = tmp->next;
//     // }
//     return (1);
// }
int is_builtin(char **args)
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
// void minishell_cmd(char *env[])
// {
// 	pid_t pid = fork();
// 		if (pid == 0)
// 		{
// 			char *args[] = {"./minishell", NULL};
// 			execve("./minishell", args, env);
// 		}
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 		}
// }
void excute_builting(t_cmd **command, t_env *env_list, char *env[])
{
	t_cmd *cmd;

	cmd = *command;

	if (strncmp("export", cmd->args[0], 6) == 0 && strlen(cmd->args[0]) == 6)
		ft_export(cmd->args, &env_list);
	else if (strncmp("env", cmd->args[0], 3) == 0 && strlen(cmd->args[0]) == 3)
		ft_env(env_list, env);
	else if (strncmp("exit", cmd->args[0], 4) == 0 && strlen(cmd->args[0]) == 4)
	{
		ft_exit(cmd->args);
		free_cmd_list(cmd);

	}
	else if (strncmp("unset", cmd->args[0], 5) == 0 && strlen(cmd->args[0]) == 5)
		ft_unset(&env_list, cmd->args + 1);
	else if (strncmp("echo", cmd->args[0], 4) == 0 && strlen(cmd->args[0]) == 4)
		echo(cmd->args);
	else if (strncmp("pwd", cmd->args[0], 3) == 0 && strlen(cmd->args[0]) == 3)
		pwd();
	else if (strncmp("cd", cmd->args[0], 2) == 0 && strlen(cmd->args[0]) == 2)
		ft_cd(cmd->args, &env_list);   
}
void check_line(t_cmd **command, t_env *env, char *en[])
{
	 t_cmd *cmd;
	  cmd = *command;
	  int fd_input = 0;
	  int fd_output = 0;
		fd_input = dup(0);
		fd_output = dup(1);  
		if (cmd->pipe_out == 1)
		{
			ft_excute_mult_pipe(cmd, env, en);
		}
	else
	{
	  while(cmd)
	  {
			if(cmd->redirs != NULL)
			{
				ft_redircte(cmd->redirs);
			}
			if(!is_builtin(cmd->args))
			{
				excute_builting(&cmd, env, en);
			}
			else
			{
				ft_excute_commands(cmd->args, &env);
			}
			cmd = cmd->next;
		}
	}
			dup2(fd_input, 0);
			dup2(fd_output, 1);
			close(fd_input);
			close(fd_output);
}
void ff()
{
	system("leaks minishell");
}
int main(int argc, char *argv[], char *env[])
{
	// atexit(ff);
	t_token *token_list;
	t_env *env_struct = NULL;   //// add to the final main
	int exit_status = 0;
	char *input;
	t_cmd *cmd;
	
	(void)argc;
	(void)argv;

	env_struct = env_maker(env, &env_struct);
	token_list = NULL;
	while (1)
	{
		input = readline("minishell $> ");
		if (!input)
			break;
		add_history(input);
		if (check_quotes(input))
		{
			// Error message already printed by check_quotes
			free(input);
			continue;
		}
		token_list = tokin_list_maker(input);
		if (token_list && !error_pipi(token_list)  && !check_syntax_errors(token_list))
		{
			// printf("--- TOKENS ---\n");
			expand_handle(token_list, env_struct, exit_status);
			//process_quotes_for_tokens(token_list, 1);
			cmd = parser(token_list);
			// ft_excute(cmd);
			check_line(&cmd, env_struct, env);
			//debug_print_cmd(cmd);
			if (cmd == NULL) {
				printf("Warning: Command list is empty after parsing!\n");
			} else {
				// process_quotes_for_cmd(cmd, 1);
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