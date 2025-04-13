CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

# Target executable name
NAME = minishell

# Source files
SRCS = builting_command.c export.c ft_split.c ft_strjoin.c libft_utils.c echo.c \
	   ft_strjoin.c 

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
INCLUDES = minishell.h

# Default target
all: $(NAME)

# Rule to compile source files to object files
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and executable
fclean: clean
	rm -f $(NAME)

# Clean and rebuild
re: fclean all

# Run the program with default parameters
run: all
	./$(NAME)

# Phony targets
.PHONY: all clean fclean re run