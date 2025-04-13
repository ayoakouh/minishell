#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_env
{
    char    *key;
    char    *value;
    int     defined;
    struct s_env *next;
} t_env;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void ft_export(char **str);
void	ft_lstadd_back(t_env **lst, t_env *new);
void echo(char **argv);


typedef struct s_command
{
    char *command;         // Command name (e.g., "ls", "grep")
    char **args;           // Array of arguments (-l , NULL-terminated)

    char *infile;          // Input redirection file (< or <<)
    int heredoc;           // 1 if heredoc (<<), 0 if regular input (<)

    char *outfile;         // Output redirection file (> or >>)
    int append;            // 1 if append mode (>>), 0 if overwrite (>)

    int pipe_out;          // 1 if command pipes to next command (|)
    struct s_command *next; // Next command in pipeline
} t_command;

#endif
