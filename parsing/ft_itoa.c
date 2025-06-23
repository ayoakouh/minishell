/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:03:24 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/21 11:01:19 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	size(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		n *= (-1);
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	itoa_hp(char *ptr)
{
	ptr[0] = '0';
	ptr[1] = '\0';
}

char	*ft_itoa(int nbr)
{
	char	*ptr;
	long	n;
	int		i;

	n = nbr;
	i = size(n);
	ptr = malloc(sizeof(char) * (i + 1));
	if (!ptr)
		return (NULL);
	ptr[i] = '\0';
	i--;
	if (n == 0)
		itoa_hp(ptr);
	if (n < 0)
	{
		ptr[0] = '-';
		n *= (-1);
	}
	while (n > 0)
	{
		ptr[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (ptr);
}

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	is_valid_var_char(char c)
{
	if (((ft_isalnum(c)) || (c == '_')))
		return (1);
	else
		return (0);
}
