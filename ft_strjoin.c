/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:52:02 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/15 15:43:56 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// static void	copy_strings(char *ptr, const char *s1, const char *s2)
// {
// 	unsigned int	i;
// 	unsigned int	j;

// 	i = 0;
// 	while (s1[i] != '\0')
// 	{
// 		ptr[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j] != '\0')
// 	{
// 		ptr[i + j] = s2[j];
// 		j++;
// 	}
// 	ptr[i + j] = '\0';
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char			*ptr;
// 	size_t			total_len;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (strdup(s2));
// 	if (!s2)
// 		return (strdup(s1));
// 	total_len = strlen(s1) + strlen(s2);
// 	ptr = (char *)malloc (sizeof(char) * (total_len + 1));
// 	if (ptr == NULL)
// 		return (NULL);
// 	copy_strings(ptr, s1, s2);
// 	return (ptr);
// }
