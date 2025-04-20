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
void check_line(char *line, t_env *env, char *en[])
{
    char **splited;
    int        i;
    
    i = 0;
    splited = ft_split(line, ' ');
    while (splited[i])
    {
        // if (ft_strncmp("cd", splited[i] , 2) == 0 && ft_strlen(splited[i]) == 2)
        //     change_dir(splited[i + 1], &env);
        if (strncmp("export", splited[i], 6) == 0 && strlen(splited[i]) == 6)
			ft_export(splited, &env);
        else if (strncmp("env", splited[i], 3) == 0 && strlen(splited[i]) == 3)
            ft_env(env, en);
        else if (strncmp("exit", splited[i], 4) == 0 && strlen(splited[i]) == 4)
            ft_exit(0);
        // else if (strncmp("./minishell", splited[i], 11) == 0 && strlen(splited[i]) ==  11)
        //     minishell_cmd(&env);
        else if (strncmp("unset", splited[i], 5) == 0 && strlen(splited[i]) == 5)
            ft_unset(&env, splited[i + 1]);
        else if (strncmp("echo", splited[i], 4) == 0 && strlen(splited[i]) == 4)
            echo(splited);
        else if (strncmp("pwd", splited[i], 3) == 0 && strlen(splited[i]) == 3)
            pwd();
        i++;
    }
    
}

int main(int argc, char *argv[], char *env[])
{
    t_env    *env_new = NULL;
    char    *line;

    (void)argv;
	(void)argc;
    if (!env || !*env)
        return (1);
    // if (argc < 0)
    //     return (0);
	env_new = env_maker(env, &env_new);
    // env_new = creat_env(env);
    // print_strcut(env_new);
    // env_cmd(env_new);
    // export(&env_new, argv[1]);
    // env_cmd(env_new);
	// t_env *tmp = 
    while (1)
    {
      line = readline("minishell->");
      if (!line && !*line)
      {
        write (2, "exit\n", 6);
        break;
      }
      add_history(line);
      check_line(line, env_new, env);
      
    }
    
    

}
// int main(int ac, char **av, char *env[])
// {
// 	t_env *tmp = NULL;
//     if(ac < 0)
// 	{
//         return 0;
// 	}
// 	ft_export(env, av, &tmp);
// }
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