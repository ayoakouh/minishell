/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <anel-men@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:36 by anel-men          #+#    #+#             */
/*   Updated: 2025/06/21 16:05:07 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <ctype.h>
# define SET 0
# define GET 1

typedef struct s_split_helper
{
	size_t	*i;
	size_t	*j;
	size_t	*start;
}	t_split_helper;

typedef struct s_extra_param
{
	char	*result;
	int		*i;
	int		*result_len;
	int		*quote_state;
	int		had_quotes;
}	t_extra_param;

typedef struct s_pre_cmd
{
	char	*input;
	char	*result;
	int		*i;
	int		*j;
}	t_pre_cmd;

typedef struct s_quote_params
{
	int		quote_state;
	char	*new_str;
	int		j;
	int		remove_mode;
	int		in_opposite_quote;
	int		i;
}	t_quote_params;

typedef struct s_add_int
{
	int		number_1;
	int		number_2;
}	t_add_int;

typedef struct t_data
{
	int		exit_status;
	char	*new_pwd;
}	t_data;

typedef struct s_token
{
	char			*data; // change to data
	char			*tokin; // change to tokin
	char			*befor_data_expand; // befor_data_expand
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_not_active;
	int				for_path;
	struct s_env	*next;
}	t_env;

typedef struct s_var
{
	char	*name;
	int		is_valid;
	int		length;
	int		name_allocated;
}	t_var;

typedef struct s_redir
{
	int				type;
	char			*file;
	int				*fd;
	int				ambiguous; // change to ambiguous
	char			*orig_token;
	char			*heredoc_delemter;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	pid_t			pid;
	int				fd[2];
	int				flag;
	char			*cmd;
	char			**args;
	t_redir			*redirs;
	t_data			data;
	int				pipe_out;
	int				fd_pipe[2];
	char			**args_befor_quotes_remover;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exp_helper
{
	char	*original;
	char	*expanded;
	int		i;
	int		j;
	int		quote_state;
	char	*var_name;
	char	*var_value;
	int		k;
	int		start;
	size_t	buffer_size;
	int		var_expanded;
	int		had_removed_var;
}	t_exp_helper;

char			*change_space(char *str);
void			cmd_extra_helper(char *str,
					t_extra_param	*extra_param, char *quote);
void			processed_cmd(t_cmd *current, char	*processed);
void			process_input_characters(t_pre_cmd *pre_cmd, int *in_quotes);
void			shift_arrays_left(t_cmd *current, int *i, int *j);
void			process_redir_helper(char str, int *quote_state);
void			scan_for_token(char *input, int *i,
					int input_length, int *start_index);
void			handle_block(char *input, int *i, int input_length,
					t_token **token_list);
void			handle_block_helper(char *input, int *i, t_token **token_list);
void			*ft_memcpy_q(void *dest, const void *src, size_t n);
void			count_words_q_hp(char s, int *quote_state);
void			split_string_q_hp0(char s, int *quote_state);
void			skip_redirections_hp(char str, int *quote_state);
void			cmd_extracter_hp_0(char str, int *quote_state);
void			check_missing_filename(char *str);
void			print_error(char *str, int *i);
void			redirection_helper(char *str, int *i, int *count);
void			cmd_extracter_hp_1(char *str, t_extra_param	*extra_param);
void			cmd_extracter_hp_2(char *str, t_extra_param	*extra_param);
void			preprocess_cmd_hp_1(t_pre_cmd *pre_cmd, int *in_quotes);
void			value_extracter(t_exp_helper *expand, t_env *env);
void			free_env_struct(t_env *env_struct);
void			free_token_list(t_token *token_list);
void			free_split_array(char **split);
void			process_quotes_for_cmd(t_cmd *cmd_list, int remove_mode);
void			process_quotes_for_cmd_hp(t_cmd *current,
					int *i, int remove_mode);
void			ft_putstr_fd(char *s, int fd);
void			print_file_error(char *file, int i);
void			file_opener(t_cmd *cmd, t_env *env);
void			ft_lstadd_back_env(t_env **lst, t_env *new);
void			ft_lstadd_back_token(t_token **lst, t_token *new);
void			add_redir_back(t_redir **lst, t_redir *new);
void			add_cmd_back(t_cmd **lst, t_cmd *new);
void			expand_handle(t_cmd *cmd_list, t_env *env, int exit_status);
void			free_redirs(t_redir *redir_list);
void			free_cmd_list(t_cmd *cmd_list);
void			ambiguous_checker(t_redir *redir);
void			free_string_array(char **array);
void			ambiguous_finder(t_cmd *cmd);
void			split_the_rest_helper(t_cmd *current, int *i);
void			split_the_rest(t_cmd *current);
void			apply_word_splitting(t_cmd *cmd_list, t_exp_helper *expand);
void			print_tokens(t_token *token_list);
void			free_split_str(char **split_str);
void			print_env(t_env *env_struct);
void			fill_num_string(char *str, long num, int len);
void			print_cmd(t_cmd *cmd_list);
void			process_string(char *str, t_exp_helper *expand,
					t_env *env, t_add_int *two_number);
void			print_ambiguous_redir_errors(t_cmd *cmd);
void			*ft_calloc(size_t nmemb, size_t size);
void			check_here_doc(t_cmd *cmd, t_env *env);
void			free_expanded(t_exp_helper *expand);
void			prepare_new_args(char **new_args, t_cmd *current, int i);

char			*ft_itoa(int n);
char			*ft_strdup(const char *s);
char			*ft_strncpy(char *dest, const char *src, unsigned int n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*redir_extracter(char *str);
char			**ft_split_q(char const *s, char c);
char			*cmd_extracter_hp_3(char *result,
					int *result_len, int had_quotes);
char			*init_cmd_buffer(char *str, int *i,
					int *result_len, int *quote_state);
char			*preprocess_command(char *input);
char			*cmd_extracter(char *str);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*chenger_back(char *str);
char			*chenger(char *str);
char			**split_if_needed(char *str);
char			*ft_strtrim(char const *s1, char const *set);
char			*change_space(char *str);
char			**free_split_q(char **split, size_t j);
char			**free_split(char **split, size_t j);
char			*allocate_and_init(char *str);
char			*selective_remove_quotes(char *str, int remove_mode);
char			*lookup_variable(char *var_name, t_env *env_struct);

int				key_is_var(char *str);
int				check_for_space(char *str);
int				is_var_key_append(char *original_arg);
int				is_append_assignment(char *str);
int				ft_strlen(const char *str);
int				signal_static(int type, int status);
int				here_doc_static(int type, int status);
int				has_quotes_in_previous_args(t_cmd *current, int current_index);
int				ft_lint(char **str);
int				helper3(t_exp_helper *expand, int exit_status, int pipe_out);
int				process_quote_char(char c, t_quote_params	*qoute_param);
int				expand_handle_helper0(t_exp_helper *expand);
int				ensure_buffer_space(t_exp_helper *expand,
					size_t additional_needed);
int				expand_fill_str(t_exp_helper *expand, char *str);
int				ft_isdigiti(int c);
int				expand_handle_helper1(t_exp_helper *expand, int exit_status,
					t_env *env, int pipe_out);
int				get_num_length(long num);
int				extracting_the_key_value(t_exp_helper *expand, int exit_status,
					t_env *env, int pipe_out);
int				var_name_extract(t_exp_helper *expand);
int				alloc_var_name(t_exp_helper *expand);
int				preprocess_cmd_hp_0(t_pre_cmd *pre_cmd, int *in_quotes);
int				is_whitespace(char c);
int				special_character_cheker(char character);
int				handle_quotes(char c, int *quote_state);
int				special_character_cheker_with_quotes(char character,
					int quote_state);
int				ft_isalnum(int c);
int				split_string_q_hp1(char **split,
					t_split_helper	*split_paramter, char const *s);
int				creat_redir_list_helper(char *str);
int				is_valid_var_char(char c);
int				*open_file(t_cmd *cmd, int type, char *file, int Ambiguous);
int				preprocess_cmd_hp_2(t_pre_cmd *pre_cmd, int *in_quotes);
int				adding_var_value(t_exp_helper *expand);
int				check_for_redirection(char *str);
int				*heredoc_opener(void);
int				invalid_filename_checker(char *str, int *i);
int				check_invalid_filename(char *str);
int				check_quotes(char *input);
int				check_quotes_helper(int in_quote);
int				print_error_pipe(void);
int				error_pipi(t_token *token_list);
int				check_syntax_errors(t_token *token_list);
int				get_or_set(int type, int status);
int				is_valid_key(char *key);
void			add_one_shlvl(t_env *env);
char			*split_helper(char *str, char *befor, int exp);
char			*handle_split_processing(char **split, char *str);
char			*process_valid_assignment(char **split, char *new_key);
char			*create_simple_assignment(char *key, char *value,
					char **split, char *new_key);
char			*create_quoted_value(char *value, char **split, char *new_key);
void			cleanup_joins(char *join1, char *join2, char *join3);
void			cleanup_split_key(char **split, char *new_key);
void			cle1(char *join1, char *join2, char *join3);
void			cle0(char **split, char *new_key);
char			*plus_checker(char *str);
char			**extract(char *str);
void			free_extract_result(char **split);
void			split_stoper_hp(t_cmd *tmp, int *i, int *exp);
void			split_stoper(t_cmd *cmd);
char			*chenger_back(char *str);
void			change_back_cmd(t_cmd *cmd);
int				rebuild_cmd_args(char **new_args, t_cmd *current, char **split,
					t_add_int	*two_numbers);
int				skip_redirections(char *str);
t_token			*creat_token(char *data, char *token_type);
t_token			*special_character_handle(char *input, int *i);
t_token			*tokin_list_maker(char *input);
t_redir			*creat_redir_list_helper0(char *str1, char *str2);
t_redir			*creat_redir_list(char *str);
t_redir			*creat_redir_node(int type, char *file);
t_cmd			*creat_cmd_node(char *str, t_token *tp, int pipe_out);
t_cmd			*parser(t_token *token_list);
t_exp_helper	*alloc_expand(void);
t_add_int		*add_two_int(int exit_status, int pipe_out);
void			ft_putchar_fd(char c, int fd);
char			*split_helper(char *str, char *befor, int exp);
void			process_redir_hp(char *str, int *start,
					int *i, int *after_operator);
void			processed_redir(t_redir *redir, char *processed);
t_pre_cmd		*init_precmd(char *input, int *i, char *result, int *j);
t_add_int		*add_two_int(int number_1, int number_2);
t_quote_params	*add_quote_params(char *new_str, int remove_mode);
t_split_helper	*split_param(size_t *i, size_t *j, size_t *start);
t_extra_param	*init_extra_param(char *result,
					int *i, int *result_len, int *quote_state);
t_env			*find_last_node(t_env *env);
void			add_shlvl_node(t_env *env);
void			split_stoper_hp(t_cmd *tmp, int *i, int *exp);
void			split_stoper(t_cmd *cmd);
char			*chenger_back(char *str);
void			change_back_cmd(t_cmd *cmd);
void			free_extract_result(char **split);
char			**extract(char *str);
char			*plus_checker(char *str);
void			cle0(char **split, char *new_key);
void			cle1(char *join1, char *join2, char *join3);
void			cleanup_split_key(char **split, char *new_key);
void			cleanup_joins(char *join1, char *join2, char *join3);
void			clean_hp(char *join1, char *join2, char **split, char *new_key);
char			*create_quoted_value(char *value, char **split, char *new_key);
char			*create_simple_assignment(char *key, char *value,
					char **split, char *new_key);
char			*process_valid_assignment(char **split, char *new_key);
char			*handle_split_processing(char **split, char *str);
char			*split_helper(char *str, char *befor, int exp);
t_env			*find_shlvl_node(t_env *env);
void			update_shlvl_value(t_env *shlvl_node);
t_env			*create_shlvl_node(void);
void			change_space_helper(char *str, int	*quote_state, int *i);

#endif
