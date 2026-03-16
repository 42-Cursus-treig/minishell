NAME = minishell

SRCDIR = srcs
BINDIR = bin
INCDIR = include
LIBFTDIR = libft

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/include
LIBS = -L$(LIBFTDIR) -lft -lreadline

BUILTINS_SRCS = $(SRCDIR)/builtins/builtins.c \
				$(SRCDIR)/builtins/echo.c \
				$(SRCDIR)/builtins/cd.c \
				$(SRCDIR)/builtins/pwd.c \
				$(SRCDIR)/builtins/export.c \
				$(SRCDIR)/builtins/unset.c \
				$(SRCDIR)/builtins/env.c \
				$(SRCDIR)/builtins/exit.c

EXECUTOR_SRCS = $(SRCDIR)/executor/executor.c \
				$(SRCDIR)/executor/execute_simple_cmd.c \
				$(SRCDIR)/executor/setup_redirections.c \
				$(SRCDIR)/executor/execute_pipeline.c \
				$(SRCDIR)/executor/execute_heredoc.c

PARSER_SRCS =	$(SRCDIR)/parser/parser.c \
				$(SRCDIR)/parser/parse_word.c \
				$(SRCDIR)/parser/expansion.c \
				$(SRCDIR)/parser/fill_argv_from_tokens.c \
				$(SRCDIR)/parser/parse_commands_from_tokens.c \
				$(SRCDIR)/parser/parse_simple_cmd.c

SIGNALS_SRCS = $(SRCDIR)/signals/signals.c

TOKENS_SRCS = 	$(SRCDIR)/tokens/handle_operator.c \
				$(SRCDIR)/tokens/tokenize.c \
				$(SRCDIR)/tokens/tokens_to_argv.c

UTILS_SRCS = 	$(SRCDIR)/utils/env_utils.c \
				$(SRCDIR)/utils/execute_utils.c \
				$(SRCDIR)/utils/export_unset_utils.c \
				$(SRCDIR)/utils/free_utils.c \
				$(SRCDIR)/utils/heredoc_utils.c \
				$(SRCDIR)/utils/parse_utils.c \
				$(SRCDIR)/utils/path_utils.c \
				$(SRCDIR)/utils/pipeline_utils.c \
				$(SRCDIR)/utils/token_utils.c

MAIN_SRCS = $(SRCDIR)/main.c

SRCS = $(BUILTINS_SRCS) $(EXECUTOR_SRCS) $(PARSER_SRCS) $(SIGNALS_SRCS) $(TOKENS_SRCS) $(UTILS_SRCS) $(MAIN_SRCS)

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFTDIR)/libft.a

all: $(LIBFT) $(NAME)

$(BINDIR):
	mkdir -p $(BINDIR)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(BINDIR)/$(NAME)

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(BINDIR)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re