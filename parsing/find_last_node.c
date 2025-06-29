/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:06:28 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/28 15:00:36 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rm_hp(int end, int start)
{
	int	new_len;

	new_len = end - start + 1;
	if (new_len < 0)
		new_len = 0;
	return (new_len);
}

void	remove_empty_quotes_inplace(char	*str)
{
	int	len;
	int	start;
	int	end;
	int	new_len;

	if (str == NULL)
		return ;
	len = ft_strlen(str);
	if (len < 2)
		return ;
	start = 0;
	while (start <= len - 2
		&& ((str[start] == '"' && str[start + 1] == '"')
			|| (str[start] == '\'' && str[start + 1] == '\'')))
		start += 2;
	end = len - 1;
	while (end >= start + 1
		&& ((str[end] == '"' && str[end - 1] == '"')
			|| (str[end] == '\'' && str[end - 1] == '\'')))
		end -= 2;
	new_len = rm_hp(end, start);
	if (start > 0 && new_len > 0)
		ft_memmove(str, str + start, new_len);
	str[new_len] = '\0';
}

int	process_string_initial(char *str, t_exp_helper *expand,
	t_env *env, t_add_int *two_number)
{
	if (!expand_fill_str(expand, str))
	{
		if (expand->expanded)
		{
			free(expand->expanded);
			expand->expanded = NULL;
		}
		free(two_number);
		return (0);
	}
	if (!process_string_loop(expand, env, two_number))
	{
		free(two_number);
		return (0);
	}
	if (expand->expanded)
		expand->expanded[expand->j] = '\0';
	expand->expanded = change_space(expand->expanded);
	return (1);
}

void	process_string_finalize(t_exp_helper *expand)
{
	char	*original_expanded;
	char	*new_expanded;
	char	*final_result;

	final_result = NULL;
	original_expanded = expand->expanded;
	change_space(original_expanded);
	new_expanded = ft_strtrim(original_expanded, " ");
	final_result = expand->expanded;
	if (new_expanded && new_expanded[0] == '\0')
	{
		free(original_expanded);
		expand->expanded = new_expanded;
		return ;
	}
	change_space(new_expanded);
	remove_empty_quotes_inplace(new_expanded);
	free(original_expanded);
	change_space(new_expanded);
	final_result = ft_strtrim(new_expanded, " ");
	free(new_expanded);
	expand->expanded = final_result;
}

void	process_string(char *str, t_exp_helper *expand,
	t_env *env, t_add_int *two_number)
{
	if (!process_string_initial(str, expand, env, two_number))
		return ;
	process_string_finalize(expand);
}
