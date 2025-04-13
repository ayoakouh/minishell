
#include "minishell.h"
// #include<stdio.h>
// #include<unistd.h>
// #include<string.h>
// #include<stdlib.h>


// typedef struct s_command
// {
//     char *command;         // Command name (e.g., "ls", "grep") ls
//     char **args;           // Array of arguments (-l , NULL-terminated) ls -la
    

//     char *infile;          // Input redirection file (< or <<)
//     int heredoc;           // 1 if heredoc (<<), 0 if regular input (<)
    
//     char *outfile;         // Output redirection file (> or >>)
//     int append;            // 1 if append mode (>>), 0 if overwrite (>)
    
//     int pipe_out;          // 1 if command pipes to next command (|)
//     struct s_command *next; // Next command in pipeline
// } t_command;

// ****************this functione is implementation of echo commande "echo";

void cd(char *path) {
    if (path == NULL) {
        path = getenv("HOME");
    }

    if (chdir(path) != 0) {
        perror("chdir");
    }
}
// void cd(int ac, char **path)
// {
//     if (ac > 2 && strcmp(path[1], "cd") == 0)
//     {
//         if (access(path[2], F_OK) == 0)
//         {
//             if (chdir(path[2]) != 0)
//             {
//                 perror("chdir");
//             }
//             else
//             {
//                 printf("Directory changed to %s\n", path[2]);
//             }
//         }
//         else
//         {
//             perror("access");
//         }
//     }
//     else 
//     {
//         fprintf(stderr, "Usage: %s cd <directory>\n", path[0]);
//         exit(1);
//     }
// }

int main(int ac, char **av)
{
	if (ac < 3)
		return (0);
	echo(av);
	// pwd(ac, av);
	cd(av[2]);
	if(strcmp(av[1], "export") == 0)
	{
	    ft_export(av);
	}
}
