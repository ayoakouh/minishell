/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:35:13 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 21:06:46 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global_sig = 0;

void	handel_signal(int sig)
{
	if (sig == SIGINT)
	{
		get_or_set(SET, 1);
		g_global_sig = 2;
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		g_global_sig = sig;
}

void	run_exuc(t_token *token_list, t_shell_var *state, int *status)
{
	t_cmd	*cmd;

	cmd = parser(token_list);
	split_stoper(cmd);
	free_token_list(token_list);
	expand_handle(cmd, state->env_struct, get_or_set(GET, 0));
	ambiguous_finder(cmd);
	process_quotes_for_cmd(cmd, 1);
	change_back_cmd(cmd);
	file_opener(cmd);
	print_ambiguous_redir_errors(cmd);
	check_line(&cmd, &state->env_struct);
	*status = cmd->data.exit_status;
	free_cmd_list(cmd);
	g_global_sig = 0;
}

void	process_tokens(t_token *token_list, t_shell_var *state, int *status)
{
	int	has_pipe_error;
	int	has_syntax_error;
	int	i;

	i = 3;
	if (!token_list)
		return ;
	has_pipe_error = error_pipi(token_list);
	has_syntax_error = check_syntax_errors(token_list);
	if (!has_pipe_error && !has_syntax_error)
	{
		run_exuc(token_list, state, status);
		while (i < 10240)
		{
			close(i);
			i++;
		}
	}
	else if (has_pipe_error || has_syntax_error)
	{
		get_or_set(SET, 258);
		free_token_list(token_list);
	}
	else
		free_token_list(token_list);
}

void	minishell_loop(t_shell_var *state, int *status)
{
	char	*input;
	char	*preprocessed_input;
	int		should_continue;
	int		r;

	while (1)
	{
		setup_signals_and_terminal();
		input = readline("minishell $> ");
		if (!input)
		{
			printf("exit\n");
			if (g_global_sig == 2)
				*status = 1;
			r = get_or_set(GET, 0);
			if (r)
				*status = r;
			break ;
		}
		add_history(input);
		preprocessed_input = process_input(input, &should_continue);
		if (should_continue)
			continue ;
		loop_helper(preprocessed_input, state, status);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_shell_var	*var;
	int			status;

	(void)argc;
	(void)argv;
	shell_mode();
	var = init_shell(env);
	status = 0;
	if (!var)
		return (1);
	minishell_loop(var, &status);
	cleanup_minishell(var);
	exit(status);
	return (0);
}
