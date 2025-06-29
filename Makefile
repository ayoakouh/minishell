
CC = gcc
CFLAGS = -Wall -Wextra  -g -fsanitize=address #--analyze

# Target executable name
NAME = minishell

# Source files
SRCS =  main_utils.c utils.c execute_utils.c export_utils.c exc_cmd.c libft_utils.c echo.c \
		main_utils_1.c cd_utils.c ft_unset.c ft_exit.c env.c export.c libft_utils1.c ft_cd.c pwd.c \
		execute_utils3.c env_null.c redrction.c ft_pipe.c main.c Heredoc_Expansion.c herdoc.c\
		execute_utils4.c heredoc_helper_0.c heredoc_helper_1.c heredoc_helper_2.c  herdoc_1.c \
		cd_utils1.c execute_utils2.c execute.c execute_utils1.c herdoc_2.c  heredoc_helper_3.c \
		parsing/Ambiguous.c             parsing/expand_utils_6.c        parsing/parser_helper.c   \
		parsing/Ambiguous_helper.c      parsing/expand_utils_7.c        parsing/parser_helper_2.c  \
		parsing/add_back_func.c         parsing/expand_utils_8.c        parsing/parser_helper_3.c   \
		parsing/add_one_shlvl.c         parsing/expand_utils_9.c        parsing/parser_helper_4.c    \
		parsing/add_shlvl_node.c        parsing/find_last_node.c        parsing/parsing_main.c        \
		parsing/debugging_tools.c       parsing/free_func.c             parsing/parsing_utiles.c       \
		parsing/expand.c                parsing/free_func_1.c           parsing/parsing_utiles_3.c \
		parsing/expand_helper_0.c       parsing/ft_itoa.c               parsing/parsing_utiles_4.c \
		parsing/expand_helper_1.c       parsing/ft_split.c              parsing/parsing_utiles_5.c\
		parsing/expand_helper_10.c      parsing/lexer.c                 parsing/parsing_utiles_6.c\
		parsing/expand_utils.c          parsing/lexer_helper_0.c        parsing/struc_maker.c\
		parsing/expand_utils_10.c       parsing/lexer_helper_1.c        parsing/syntx_check.c\
		parsing/expand_utils_11.c       parsing/open_files.c            parsing/syntx_check_helper_0.c\
		parsing/expand_utils_12.c       parsing/open_files_helper.c     parsing/syntx_check_helper_1.c\
		parsing/expand_utils_4.c        parsing/parser.c\
		parsing/expand_utils_5.c        parsing/parser_0.c
# Object files
OBJS = $(SRCS:.c=.o)

# Header files
INCLUDES = minishell.h

# Default target
all: $(NAME)

LDLIBS = -lreadline

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and executable
fclean: clean
	rm -f $(NAME)

# Clean and rebuild
re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run


# CC = gcc
# CFLAGS = -Wall -Wextra #-g -fsanitize=address

# # Target executable name
# NAME = minishell

# # Source files
# SRCS = r.c ft_split.c libft_utils.c echo.c \
# 		ft_unset.c ft_exit.c env.c export.c ft_cd.c pwd.c \
# 		env_null.c redrction.c
# 		lll.c      
# 	    parser_helper_4.c \
# 	    main.c 
		
		 
				 

# # Object files
# OBJS = $(SRCS:.c=.o)

# # Header files
# INCLUDES = minishell.h

# # Default target
# all: $(NAME)

# LDLIBS = "-lreadline"

# %.o: %.c $(INCLUDES)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Rule to link object files into the executable
# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

# # Clean object files
# clean:
# 	rm -f $(OBJS)

# # Clean object files and executable
# fclean: clean
# 	rm -f $(NAME)

# # Clean and rebuild
# re: fclean all

# run: all
# 	./$(NAME)

# .PHONY: all clean fclean re run



# CC = gcc
# CFLAGS = -Wall -g -fsanitize=address

# # Target executable name
# NAME = minishell

# # Source files
# SRCS = Ambiguous.c  echo.c  et.c  expand_utils.c  ft_cd.c ft_unset.c  lexer_helper_1.c  parser_helper_1.c \
# 		pwd.c syntx_check_helper_0.c Heredoc_Expansion.c env.c expand.c export.c ft_exit.c libft_utils.c \   
# 		open_files.c parser_helper_2.c r.c syntx_check_helper_1.c ft_itoa.c lexer.c lll.c parser.c \
# 		add_back_func.c env_helper.c expand_helper_0.c free_func.c \              
# 		parser_helper_4.c redrction.c parser_helper.c parsing_main.c  syntx_check.c main.c \ 
# 		debugging_tools.c env_null.c expand_helper_1.c free_func_1.c ft_split.c lexer_helper_0.c          
		

# # r.c ft_split.c ft_strjoin.c libft_utils.c echo.c \
# # 		ft_unset.c ft_exit.c env.c export.c ft_cd.c pwd.c \
# # 		env_null.c redrction.c add_back_func.c         lexer_helper_0.c \
# # 		debugging_tools.c       lexer_helper_1.c \
# # 		 parser.c     parser_helper.c 	lll.c	\
# # 		expand.c                parser_helper_1.c \
# # 		expand_helper_0.c       parser_helper_2.c \
# # 		expand_helper_1.c       parser_helper_4.c \
# # 		free_func.c          	main.c \
# # 		free_func_1.c           syntx_check.c \
# # 		ft_itoa.c               syntx_check_helper_0.c \
# # 		lexer.c                 syntx_check_helper_1.c \
# # Object files
# OBJS = $(SRCS:.c=.o)

# # Header files
# INCLUDES = minishell.h

# # Default target
# all: $(NAME)

# LDLIBS = -lreadline

# %.o: %.c $(INCLUDES)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Rule to link object files into the executable
# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

# # Clean object files
# clean:
# 	rm -f $(OBJS)

# # Clean object files and executable
# fclean: clean
# 	rm -f $(NAME)

# # Clean and rebuild
# re: fclean all

# run: all
# 	./$(NAME)

# .PHONY: all clean fclean re run