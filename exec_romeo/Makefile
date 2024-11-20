# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Executable name
NAME = minishell

# Directories
SRCDIR = .
BUILTINDIR = $(SRCDIR)/built_in
EXECDIR = $(SRCDIR)/exec
REDIRDIR = $(SRCDIR)/redirections

# Source files
SRCS = $(wildcard $(BUILTINDIR)/*.c) \
       $(wildcard $(EXECDIR)/*.c) \
       $(wildcard $(REDIRDIR)/*.c) \
       $(SRCDIR)/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = $(SRCDIR)/minishell.h

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
