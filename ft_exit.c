/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:26:45 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 14:39:54 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_space(const char **str, int sign)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	return (sign);
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

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
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
	//n = atoi();

// if ((n == LONG_MAX && ft_strcmp(args[1], "9223372036854775807") != 0))
// {
//     ft_putendl_fd("exit: numeric argument required", 2);
//     data.exit_status = get_or_set(SET, 255);
//     exit(255);
// }
// void    ft_exit(char **args)
// {
//     long n ;
//     if(!args || !args[1])
//         exit(0);
//     if(!is_numeric(args[1]))
//     {
//         write(2, "exit: ", 6);
//         write(2, &args[1], ft_strlen(args[1]));
//         write(2, ": numeric argument required", 27);
//         exit(2);
//     }
//     if(args[2])
//     {
//         write(2, "exit", 4);
//        write(2, " exit: too many argument\n", 24); 
//        return ;
//     }
//     n = ft_atoi(args[1]);
//     if(ft_strcmp(args[1], "9223372036854775807") != 0 && n == LONG_MAX)
//     {
//         exit(255);
//     }
//     printf("exit\n");
// }
// void minishell_exit(char **args, t_env *shell)
// {
//     // if (!is_child_process)
//     //     ft_putendl_fd("exit", 1);

//     if (!args[1])
//     {
//         // free_all(shell);
//         exit(shell->last_exit_status);
//     }
//     if (!is_numeric(args[1]))
//     {
//         ft_putstr_fd("minishell: exit: ", 2);
//         ft_putstr_fd(args[1], 2);
//         ft_putendl_fd(": numeric argument required", 2);
//         // free_all(shell);
//         exit(255);
//     }
//     if (args[2])
//     {
//         ft_putendl_fd("minishell: exit: too many arguments", 2);
//         shell->last_exit_status = 1;
//         return;
//     }
//     long exit_status = atoi(args[1]);
//     // free_all(shell);
//     exit((unsigned char)exit_status);
// }
// void ft_exit(t_env **env_list, char **str)
// {
// }