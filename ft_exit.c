/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:26:45 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/28 21:21:08 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long	check_over_flow(long n)
{
	n = n % 256;
	if (n < 0)
		n += 256;
	return (n);
}

int	ft_exit(char **args, t_data data)
{
	long	n;

	n = 0;
	if (isatty(0) && isatty(1))
		printf("exit\n");
	if (!args || !args[1])
		exit(get_or_set(GET, 0));
	n = ft_atoi(args[1]);
	if (!is_numeric(args[1])
		|| (n == LONG_MAX && ft_strcmp(args[1], "9223372036854775807") != 0)
		|| (n == LONG_MIN && ft_strcmp(args[1], "-9223372036854775808") != 0))
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		data.exit_status = get_or_set(SET, 255);
		exit(255);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: too many arguments", 2);
		data.exit_status = get_or_set(SET, 1);
		return (1);
	}
	n = check_over_flow(n);
	data.exit_status = get_or_set(SET, (int)n);
	exit(data.exit_status);
}
