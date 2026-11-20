NAME			= minishell

CC				= cc
CFLAGS			= -Wall -Wextra -Werror

SRCDIR			= srcs
INCDIR			= include
BINDIR			= bin
LIBFTDIR		= libft

TARGET			= $(BINDIR)/$(NAME)
LIBFT			= $(LIBFTDIR)/libft.a
INCLUDES		= -I$(INCDIR) -I$(LIBFTDIR)/include
LIBS			= -L$(LIBFTDIR) -lft -lreadline

CLANG_FORMAT	= clang-format
DOXYGEN			= doxygen

MAIN_SRCS		= $(SRCDIR)/main.c

BUILTINS_SRCS	= $(SRCDIR)/builtins/builtins.c \
				  $(SRCDIR)/builtins/cd.c \
				  $(SRCDIR)/builtins/echo.c \
				  $(SRCDIR)/builtins/env.c \
				  $(SRCDIR)/builtins/exit.c \
				  $(SRCDIR)/builtins/export.c \
				  $(SRCDIR)/builtins/pwd.c \
				  $(SRCDIR)/builtins/unset.c

EXECUTOR_SRCS	= $(SRCDIR)/executor/executor.c \
				  $(SRCDIR)/executor/execute_heredoc.c \
				  $(SRCDIR)/executor/execute_pipeline.c \
				  $(SRCDIR)/executor/execute_simple_cmd.c \
				  $(SRCDIR)/executor/setup_redirections.c

PARSER_SRCS		= $(SRCDIR)/parser/parser.c \
				  $(SRCDIR)/parser/expansion.c \
				  $(SRCDIR)/parser/fill_argv_from_tokens.c \
				  $(SRCDIR)/parser/parse_commands_from_tokens.c \
				  $(SRCDIR)/parser/parse_simple_cmd.c \
				  $(SRCDIR)/parser/parse_word.c

SIGNALS_SRCS	= $(SRCDIR)/signals/signals.c

TOKENS_SRCS		= $(SRCDIR)/tokens/handle_operator.c \
				  $(SRCDIR)/tokens/tokenize.c \
				  $(SRCDIR)/tokens/tokens_to_argv.c

UTILS_SRCS		= $(SRCDIR)/utils/env_utils.c \
				  $(SRCDIR)/utils/execute_utils.c \
				  $(SRCDIR)/utils/export_unset_utils.c \
				  $(SRCDIR)/utils/free_utils.c \
				  $(SRCDIR)/utils/heredoc_utils.c \
				  $(SRCDIR)/utils/parse_utils.c \
				  $(SRCDIR)/utils/path_utils.c \
				  $(SRCDIR)/utils/pipeline_utils.c \
				  $(SRCDIR)/utils/token_utils.c

SRCS			= $(MAIN_SRCS) \
				  $(BUILTINS_SRCS) \
				  $(EXECUTOR_SRCS) \
				  $(PARSER_SRCS) \
				  $(SIGNALS_SRCS) \
				  $(TOKENS_SRCS) \
				  $(UTILS_SRCS)

OBJS			= $(SRCS:.c=.o)

FMT_FILES		= $(SRCS) $(wildcard $(INCDIR)/*.h)

# **************************************************************************** #
#                                    BUILD                                     #
# **************************************************************************** #

all: $(LIBFT) $(TARGET)

$(TARGET): $(OBJS) $(LIBFT) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(BINDIR)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

format:
	$(CLANG_FORMAT) -i --style=file $(FMT_FILES)

format-check:
	$(CLANG_FORMAT) --dry-run --Werror --style=file $(FMT_FILES)

doc:
	$(DOXYGEN) Doxyfile

.PHONY: all clean fclean re format format-check doc
