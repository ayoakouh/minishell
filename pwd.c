/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:34:07 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/24 18:27:44 by ayoakouh         ###   ########.fr       */
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
