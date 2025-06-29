/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:51:25 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/26 10:53:09 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	find_quote_end(const char *str, int len)
{
	int	i;

	i = 0;
	while (i < len && is_quote(str[i]))
		i++;
	return (i);
}

int	find_quote_start(const char *str, int len)
{
	int	i;

	i = len - 1;
	while (i >= 0 && is_quote(str[i]))
		i--;
	return (i);
}

int	count_spaces_after(const char *str, int start, int len)
{
	int	count;

	count = 0;
	while (start + count < len && str[start + count] == ' ')
		count++;
	return (count);
}

int	count_spaces_before(const char *str, int end)
{
	int	count;

	count = 0;
	while (end - count >= 0 && str[end - count] == ' ')
		count++;
	return (count);
}
