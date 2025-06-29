/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:25:04 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/29 10:09:43 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_sig(t_cmd **cmd)
{
	if (cmd == NULL || *cmd == NULL)
		return ;
}

void	clean_all_up(void)
{
	int	i;

	i = 3;
	while (i < 10240)
	{
		close(i);
		i++;
	}
}

t_shell_var	*init_shell(char **env)
{
	t_shell_var	*var;

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

void	setup_signals_and_terminal(void)
{
	desable_echo_term();
	signal(SIGINT, handel_signal);
	signal(SIGQUIT, SIG_IGN);
}

t_token	*create_token_list(char *preprocessed_input)
{
	char	*new_input;
	t_token	*token_list;

	new_input = change_space(preprocessed_input);
	token_list = tokin_list_maker(new_input);
	free(preprocessed_input);
	return (token_list);
}
