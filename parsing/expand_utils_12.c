/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_12.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:57:06 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/27 15:53:37 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_exp_helper	*alloc_expand(void)
{
	t_exp_helper	*expand;

	expand = malloc(sizeof(t_exp_helper));
	if (!expand)
	{
		write(2, "minishell: memory allocation failed\n", 37);
		exit(1);
	}
	expand->buffer_size = 0;
	expand->expanded = NULL;
	expand->var_name = NULL;
	expand->var_value = NULL;
	expand->had_removed_var = 0;
	return (expand);
}

char	*change_space(char *str)
{
	int	i;
	int	quote_state;

	i = 0;
	quote_state = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			if (quote_state == 0)
				quote_state = 1;
			else if (quote_state == 1)
				quote_state = 0;
		}
		else if (str[i] == '"')
		{
			if (quote_state == 0)
				quote_state = 2;
			else if (quote_state == 2)
				quote_state = 0;
		}
		change_space_helper(str, &quote_state, &i);
		i++;
	}
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (dest == src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	sign = 1;
	i = 0;
	res = 0;
	sign = ft_space(&str, sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1)
		{
			if (res > (LONG_MAX - (str[i] - '0')) / 10)
				return (LONG_MAX);
		}
		else
		{
			if (res > (LONG_MAX - (str[i] - '0')) / 10)
				return (LONG_MIN);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
