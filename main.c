/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:22:58 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/04/18 13:28:01 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char *env[])
{
    if (ac < 0)
        return 0;
	t_env **tmp = NULL;
	// char **str
	ft_export(env, av, tmp);
}
	// t_env *head;
	// t_env *node1;
	// t_env *node2;
	// t_env *node3;
	
	// node1 = malloc(sizeof(t_env));
	// node2 = malloc(sizeof(t_env));
	// node3 = malloc(sizeof(t_env));

	// node1->key = strdup("PWD");
	// node1->value = strdup("/ayoub/");
	// node2->key = strdup("HOME");
	// node2->value = strdup("/mnt/homes/ayoakouh");
	// node3->key = strdup("ali");
	// node3->value = strdup("333333");

	// head = node1;
	// node1 ->next = node2;
	// node2 ->next = node3;
	// node3 ->next = NULL;
    // // ft_unset(&head, av[2]);
	// // updat_env(head, "ali", "ayoub");
	// // ft_cd(av[2], &head);
	// // cd(av);
	// puts("---------");
	// ft_exit(av);
	// // remove_env(&head, "ali");
	// t_env *tmp;
	// tmp = head;
	// // minishell_exit(av, head);
	// while(tmp)
	// {
	// 	printf("key is : %s\n", tmp->key);
	// 	printf("value is : %s\n", tmp->value);
	// 	tmp = tmp->next;
	// }
	// // cd (av, head);
// }