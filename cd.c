/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:29:34 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/12 20:37:59 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int cd(char *path)
{
    char *home;

    if (path == NULL)
    {
        home = getenv("HOME"); 
        if (home == NULL)
        {
            perror("cd");
            return (1); 
        }
        path = home;
    }

    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}
int main(int ac, char **av)
{
    if(ac < 0)
        return (0);
        
    int r = cd(av[2]);
}