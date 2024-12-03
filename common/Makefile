# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilibft -g
LDFLAGS = -lreadline
RM = rm -f

# Executable name
NAME = minishell

# Directories
SRC = src
LIBFT = libft

# Source files
SRCS = $(wildcard $(SRC)/*.c) $(wildcard $(LIBFT)/*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = inc/minishell.h

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
