/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:08:09 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/27 16:30:33 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	exp_hp(t_exp_helper *expand)
{
	if (expand && expand->original && expand->i > 0
		&& expand->original[expand->i] != '\0'
		&& expand->original[expand->i + 1] != '\0'
		&& expand->original[expand->i - 1] == '\"'
		&& expand->original[expand->i] == '$'
		&& expand->original[expand->i + 1] == '\"')
		return (0);
	return (1);
}

int	expand_handle_helper1(t_exp_helper *expand,
			t_env *env, int pipe_out, int last_node)
{
	char	*var;
	int		extracting;
	int		res_adding_var;

	var = NULL;
	if (exp_hp(expand) == 0)
		return (0);
	if (expand->original[expand->i] == '$' && expand->quote_state != 1)
	{
		expand->i++;
		extracting = extracting_the_key_value(expand,
				env, pipe_out, last_node);
		if (extracting == 0)
			return (0);
		if (expand->var_value)
		{
			res_adding_var = adding_var_value(expand);
			if (res_adding_var == 0)
				return (0);
		}
		else if (extracting == 1)
			return (1);
		return (1);
	}
	return (0);
}

int	process_string_loop(t_exp_helper *expand, t_env *env,
		t_add_int *two_number)
{
	while (expand->original[expand->i])
	{
		if (!expand_handle_helper0(expand) && !expand_handle_helper1(expand,
				env, two_number->number_2, two_number->number_3))
		{
			if (!ensure_buffer_space(expand, 1))
			{
				free(expand->expanded);
				expand->expanded = NULL;
				return (0);
			}
			expand->expanded[expand->j++] = expand->original[expand->i++];
		}
	}
	return (1);
}

char	*handle_quotes_and_spaces(const char *str)
{
	char	*result;
	int		len;

	result = create_result_string(str);
	if (!result)
		return (NULL);
	len = ft_strlen(result);
	handle_opening_spaces(result, &len);
	handle_closing_spaces(result, &len);
	return (result);
}

void	process_helper(char *new_expanded, char	*final_result,
			char	*original_expanded, t_exp_helper *expand)
{
	change_space(new_expanded);
	final_result = handle_quotes_and_spaces(new_expanded);
	free(original_expanded);
	free(new_expanded);
	expand->expanded = final_result;
	printf("________{%s}______\n", expand->expanded);
}
