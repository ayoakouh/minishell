/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahmada <kahmada@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:24:15 by kahmada           #+#    #+#             */
/*   Updated: 2024/06/01 08:23:20 by kahmada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <limits.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	char	**cmd_args;
	int		fd_in;
	char	*infile;
	char	*outfile;
	char	**envp;
}	t_list;
void	error(void);
void	split_and_check(char *arg, char ***cmd_args);
int		check_arguments(char *argv[], int argc);
int		is_whitespace_or_tab(char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_2(char *s1, char *s2);
char	**ft_split_lib(char const *s, char c);
char	**ft_split(char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*find_commande(char *cmd, char **envp);
int		handle_here_doc(const char *limiter);
void	execute_command(int in_fd, int out_fd, char **cmd_args, char *envp[]);
void	setuppipesandexecute(int inf_fd, int out_fd, char *av[], char *envp[]);
void	fork_and_execute_command(int in_fd, int out_fd,
			char *cmd, char *envp[]);
void	child_proc2(char **cmd_arg, int pi_fd[],
			char *envp[], const char *outf);
void	handle_here_doc_and_execute(char *argv[], int fd_in, char *envp[]);
void	setup_fork_procs(t_list *proc1_info, t_list *proc2_info, int pipefd[]);
void	cleanup_2darray(char **cmd_args1, char **cmd_args2);
int		ft_check(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*get_next_line(int fd);
#endif
