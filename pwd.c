/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:34:07 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/13 11:15:51 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if(!path)
		return ;
	printf("%s\n", path);
	free(path);
}

// int	pwd(char *str)
// {
// 	char	*path;
// 	char *helper;
	
// 	path = getcwd(NULL, 0);
// 	if (!path)
// 		return ;
// 	path = helper;
// 	if(strcmp(path, helper) == 0)
// 		printf("%s\n", path);
// 	else
// 	{
// 		free(path);
// 		free(helper);
// 		path = getcwd(NULL, 0);
// 		printf("%s\n", path);
// 		return (0);
// 	}
	
// }
