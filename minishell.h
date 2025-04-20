#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>




typedef struct s_env
{
    char    *key;
    char    *value;
    int    operation;
    int     last_exit_status;
    struct s_env *next;
} t_env;



char	*ft_strchr(char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_lstadd_back(t_env **lst, t_env *new);
void echo(char **argv);
int    ft_strcmp(char *s1, char *s2);
void del(void *content);
// void remove_env(t_env **env_list, char *variable);
// void ft_unset(t_env **env_list, char *variable);
void ft_unset(t_env **env_list, char *variables);
int remove_env(t_env **env_list, char *variable);
void    ft_exit(char **args);
void	ft_putstr_fd(char *s, int fd);
void ft_env(t_env *env_list, char *env[]);

t_env *env_maker(char *env[], t_env **env_struct);
void ft_export(char **str, t_env **env_list);
void updat_env(t_env **env_list, char *key, char *value);
void pwd(void);




// typedef struct s_command
// {
//     char *command;         // Command name (e.g., "ls", "grep")
//     char **args;           // Array of arguments (-l , NULL-terminated)

//     char *infile;          // Input redirection file (< or <<)
//     int heredoc;           // 1 if heredoc (<<), 0 if regular input (<)

//     char *outfile;         // Output redirection file (> or >>)
//     int append;            // 1 if append mode (>>), 0 if overwrite (>)

//     int pipe_out;          // 1 if command pipes to next command (|)
//     struct s_command *next; // Next command in pipeline
// } t_command;

#endif
