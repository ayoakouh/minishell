/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:26:22 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/28 20:26:25 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dir(int j, int dir_size, char **dir)
{
	while (j < dir_size)
	{
		if (dir[j] != NULL)
			free(dir[j]);
		j++;
	}
}
