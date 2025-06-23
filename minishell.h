/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:47:52 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/23 14:43:33 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>

# include "parsing/parsing.h"


typedef struct s_shell_var
{
    t_env *env_struct;
    struct termios infos;
    int exit_status;
    char **env;
} t_shell_var;


t_shell_var *init_shell(char **env);

char	*ft_strchr(char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_lstadd_back(t_env **lst, t_env *new);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**free_split(char **split, size_t j);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
int		echo(char **argv);
int		ft_strcmp(char *s1, char *s2);
void	del(void *content);
int		ft_unset(t_env **env_list, char **variables);
int		remove_env(t_env **env_list, char *variable);
int		is_valid_key(char *key);
int		ft_exit(char **args, t_data data);
int		ft_env(t_cmd *cmd, t_env *env_list);
t_env	*env_maker(char *env[], t_env **env_struct);
int		ft_export(char **str, t_env **env_list);
void	updat_env(t_env **env_list, char *key, char *value);
int		pwd(t_cmd *cmd);
char	*get_value_env(char *key, t_env **list);
void	ft_excute_commands(t_cmd *cmd, t_env **env_list, int flag);
t_env	*env_null(void);
int		ft_cd(char **str, t_env **list, t_cmd *cmd);
void	ft_free_split(char **str);
void	value_empty(t_env **env_list, char *key);
int		get_or_set(int type, int status);
void	wait_for_children(t_cmd *cmd, pid_t child_pid);
void	intialize_struct(t_redir *list);
int		ft_redircte(t_redir *rederction);
void	check_sig(t_cmd **cmd);
void	check_line(t_cmd **command, t_env **env_list, char *env[]);
int		exec_builtin(char **args);
void	minishell_cmd(char *env[]);
int		ft_list_size(t_env *begin_list);
char	*check_path(t_env **list);
void	restory_window(t_cmd *cmd);
void	execute_single_command(t_cmd *cmd, t_env **list_env,
			char *env[], int flag);
void	check_here_doc(t_cmd *cmd, t_env *env);
void	check_close_red(t_cmd *cmd, t_cmd *prev, t_env *env);
char	*selective_remove_quotes(char *str, int remove_mode);
int		is_builtin(char **args);
void	excute_builting(t_cmd **command, t_env **env_list, char *env[]);
char	**convert_env_list(t_env **list);
void	handel_signal(int sig);
void	ft_excute_mult_pipe(t_cmd *cmd, t_env *list_env, char *env[]);
t_env	*creat_new_env(char *key, char *value);
void	check_directory(t_cmd *cmd);
void	desable_echo_term(void);
char	*get_set(char *type, int flag);
void	handle_child(t_cmd *cmd, t_env *env_list, char *env[]);
void	heredoc(char *delmeter, t_env *env, int exit_status, 
        char *orig_delimiter, int fd);
char	*process_heredoc_epxand(char *line, t_env *env, int exit_status,
			char *orig_delimiter);
void	close_redirection(t_redir *redirs);
void	close_heredoc_fds(t_redir *redir);
void	kill_and_wait_all(t_cmd *cmd);
void	close_all_pipes(t_cmd *cmd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_isdigit(int c);
void	set_value_env(t_env **env, char *key, char *value);
void	updat_env(t_env **env_list, char *key, char *value);
char	*get_path(char *str, t_env **list);
char	*get_value(char *str);
int		ft_check(t_env *env_list, char *key);
char	*get_key(char *str);
t_env	*sort_env(t_env **head);
void	set_env(t_env **env, char *key, char *value);
int		check_append(char *str);
int		is_invalid_key(char *str, char *key, int *status);
void	_print_error(t_cmd **cmd, char *str, int i);
void	check_directory(t_cmd *cmd);
void	wait_for_children(t_cmd *cmd, pid_t child_pid);
void	if_path_null(t_cmd **cmd, char *env[]);
void	ft_print_error(t_cmd *cmd, int flag);
int		should_skip_export(char *str, t_env **lst, char *key, char *value);
int     check_home(t_env **list, char *str);
void	fork_to_child(t_cmd *cmd, char **help);
void	write_error(t_cmd *cmd);
void	check_is_derctory(t_cmd *cmd, char *path);
void	restart_setting_term(void);

#endif

// #ifndef MINISHELL_H
// # define MINISHELL_H
// #include <sys/stat.h>
// #include <errno.h>
// #include <signal.h>
// #include <sys/stat.h>
// #include <termios.h>
// #include "parsing/parsing.h"


// char	*ft_strchr(char *s, int c);
// char	**ft_split(char const *s, char c);
// char	*ft_strjoin(char const *s1, char const *s2);
// void	ft_lstadd_back(t_env **lst, t_env *new);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	**free_split(char **split, size_t j);
// void	ft_lstadd_back_env(t_env **lst, t_env *new);
// int		echo(char **argv);
// int		ft_strcmp(char *s1, char *s2);
// void	del(void *content);
// int		ft_unset(t_env **env_list, char **variables);
// int		remove_env(t_env **env_list, char *variable);
// int		is_valid_key(char *key);
// int		ft_exit(char **args, t_data data);
// int		ft_env(t_cmd *cmd, t_env *env_list);
// t_env	*env_maker(char *env[], t_env **env_struct);
// int		ft_export(char **str, t_env **env_list);
// void	updat_env(t_env **env_list, char *key, char *value);
// int		pwd(t_cmd *cmd);
// char	*get_value_env(char *key, t_env **list);
// void	ft_excute_commands(t_cmd *cmd, t_env **env_list, int flag);
// t_env	*env_null();
// int		ft_cd(char **str, t_env **list, t_cmd *cmd);
// void	ft_free_split(char **str);
// void	value_empty(t_env **env_list, char *key);
// char	*get_value_env(char *key, t_env **list);
// int		get_or_set(int type, int status);
// void	wait_for_children(t_cmd *cmd, pid_t child_pid);
// void	intialize_struct(t_redir *list);
// int		ft_redircte(t_redir *rederction, t_env *env, t_cmd *cmd);
// void	check_sig(t_cmd *cmd);
// void	check_line(t_cmd **command, t_env **env_list, char *env[]);
// int		exec_builtin(char **args);
// void	minishell_cmd(char *env[]);
// int		ft_list_size(t_env *begin_list);
// char	*check_path(t_env **list);
// void	restory_window(t_cmd *cmd);
// void	execute_single_command(t_cmd *cmd, t_env **list_env, char *env[], int flag);
// void	check_here_doc(t_cmd *cmd, t_env *env);
// void	check_close_red(t_cmd *cmd, t_cmd *prev, t_env *env);
// char	*selective_remove_quotes(char *str, int remove_mode);
// int		is_builtin(char **args);
// void	excute_builting(t_cmd **command, t_env **env_list, char *env[]);
// char	**convert_env_list(t_env **list);
// void	handel_signal(int sig);
// void	ft_excute_mult_pipe(t_cmd *cmd, t_env *list_env, char *env[]);
// t_env	*creat_new_env(char *key, char *value);
// void	handel_signal(int sig);
// void	check_directory(t_cmd *cmd);
// void	desable_echo_term();
// char	*get_set(char *type, int flag);
// void	handle_child(t_cmd *cmd, t_env *env_list, char *env[], pid_t child_pid);
// void	check_here_doc(t_cmd *cmd, t_env *env);
// void	heredoc(char *delmeter, t_env *env, int exit_status, char *orig_delimiter, int fd);
// char	*process_heredoc_epxand(char *line, t_env *env, int exit_status, char *orig_delimiter);
// void	restory_window(t_cmd *cmd);
// void	close_redirection(t_redir *redirs);
// void	close_heredoc_fds(t_redir *redir);
// void	kill_and_wait_all(t_cmd *cmd);
// void	close_all_pipes(t_cmd *cmd);
// void	ft_putendl_fd(char *s, int fd);
// char	*ft_strnstr(const char *big, const char *little, size_t len);
// int		ft_isdigit(int c);
// // void	ft(char **args, t_env **list);
// #endif