/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:34:42 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/26 18:46:25 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*lookup_variable(char *var_name, t_env *env_struct)
{
	t_env	*tmp;

	tmp = env_struct;
	while (tmp)
	{
		if (ft_strcmp(var_name, tmp->key) == 0)
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	expand_fill_str(t_exp_helper *expand, char *str)
{
	size_t	original_len;

	expand->original = str;
	original_len = ft_strlen(str);
	if (original_len > SIZE_MAX / 2 - 1024)
	{
		write(2, "minishell: memory allocation failed: input too large\n", 54);
		return (0);
	}
	expand->buffer_size = original_len * 2 + 1024;
	expand->expanded = malloc(expand->buffer_size);
	if (!expand->expanded)
	{
		write(2, "minishell: memory allocation failed\n", 37);
		return (0);
	}
	expand->i = 0;
	expand->j = 0;
	expand->quote_state = 0;
	expand->var_name = NULL;
	expand->var_value = NULL;
	return (1);
}

void	process_quotes_for_cmd_hp(t_cmd *current, int *i, int remove_mode)
{
	char	*processed;

	if (current->args)
	{
		*i = 0;
		while (current->args[*i])
		{
			processed = (selective_remove_quotes(
						current->args[*i], remove_mode));
			if (processed)
			{
				free(current->args[*i]);
				current->args[*i] = processed;
			}
			(*i)++;
		}
	}
	if (current->cmd)
	{
		*i = 0;
		processed = selective_remove_quotes(current->cmd, remove_mode);
		if (processed)
			processed_cmd(current, processed);
	}
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	m;

	i = 0;
	m = c;
	while (s[i] != '\0')
	{
		if (s[i] == m)
			return ((char *)&s[i]);
		i++;
	}
	if (m == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
