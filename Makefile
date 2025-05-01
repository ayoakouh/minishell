CC = gcc
CFLAGS = -Wall -g -fsanitize=address

# Target executable name
NAME = minishell

# Source files
SRCS = et.c ft_split.c ft_strjoin.c libft_utils.c echo.c \
		ft_unset.c ft_exit.c env.c exp.c ft_cd.c pwd.c \
		env_null.c redrction.c add_back_func.c         lexer_helper_0.c \
		debugging_tools.c       lexer_helper_1.c \
		 parser.c     parser_helper.c 	ft_pipe.c	\
		expand.c                parser_helper_1.c \
		expand_helper_0.c       parser_helper_2.c \
		expand_helper_1.c       parser_helper_4.c \
		free_func.c             main.c \
		free_func_1.c           syntx_check.c \
		ft_itoa.c               syntx_check_helper_0.c \
		lexer.c                 syntx_check_helper_1.c \


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
# CFLAGS = -Wall -Wextra -Werror -lreadline -g -fsanitize=address

# # Target executable name
# NAME = minishell

# # Source files
# SRCS = et.c export.c ft_split.c ft_strjoin.c libft_utils.c echo.c \
# 		ft_unset.c  main.c ft_exit.c env.c exp.c ft_cd.c pwd.c \
# 		env_null.c 


# # Object files
# OBJS = $(SRCS:.c=.o)

# # Header files
# INCLUDES = minishell.h

# # Default target
# all: $(NAME)

# LDLIBS = -lreadline
# # Rule to compile source files to object files
# %.o: %.c $(INCLUDES)
# 	$(CC) $(CFLAGS) -c $< -o $@ 

# # Rule to link object files into the executable
# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)

# # Clean object files
# clean:
# 	rm -f $(OBJS)
