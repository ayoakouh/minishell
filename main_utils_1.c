/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:28:21 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/28 20:32:44 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_input(char *input, int *should_continue)
{
	char	*preprocessed_input;

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

void	cleanup_minishell(t_shell_var *state)
{
	if (state)
	{
		free_env_struct(state->env_struct);
		free(state);
	}
}

void	shell_mode(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!isatty(1) || !isatty(0) || !current_dir)
	{
		if (current_dir)
			free(current_dir);
		exit(1);
	}
	free(current_dir);
}
