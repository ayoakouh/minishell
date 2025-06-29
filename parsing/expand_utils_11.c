/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_11.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:54:15 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/27 16:43:44 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	shift_left(char *str, int from, int to_remove, int *len)
{
	int	i;

	i = from;
	while (i < *len - to_remove)
	{
		str[i] = str[i + to_remove];
		i++;
	}
	*len -= to_remove;
	str[*len] = '\0';
}

void	shift_closing_left(char *str, int quote_start, int spaces, int *len)
{
	int	closing_start;
	int	i;

	closing_start = quote_start + 1;
	i = 0;
	while (i < *len - closing_start)
	{
		str[quote_start - spaces + 1 + i] = str[closing_start + i];
		i++;
	}
	*len -= spaces;
	str[*len] = '\0';
}

void	handle_opening_spaces(char *result, int *len)
{
	int	quote_end;
	int	spaces;

	quote_end = find_quote_end(result, *len);
	if (quote_end > 0)
	{
		spaces = count_spaces_after(result, quote_end, *len);
		if (spaces > 0)
			shift_left(result, quote_end, spaces, len);
	}
}

void	handle_closing_spaces(char *result, int *len)
{
	int	quote_start;
	int	spaces;

	quote_start = find_quote_start(result, *len);
	if (quote_start < *len - 1)
	{
		spaces = count_spaces_before(result, quote_start);
		if (spaces > 0)
			shift_closing_left(result, quote_start, spaces, len);
	}
}

char	*create_result_string(const char *str)
{
	int		len;
	char	*result;

	if (!str || ft_strlen(str) == 0)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, str);
	return (result);
}
