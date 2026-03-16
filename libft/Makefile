NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = srcs
INCDIR = include

MANDATORY = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strcpy.c ft_strncpy.c \
			ft_strlcpy.c ft_strcat.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c get_next_line.c

ADDITIONAL = ft_substr.c ft_strjoin.c ft_strstr.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c

PRINTF_SRCS = ft_printf.c ft_putnbr.c ft_putchar.c ft_putstr.c ft_putadress.c \
			ft_putunsnbr.c ft_putlowhexa.c ft_puthighhexa.c

SRCS = $(addprefix $(SRCDIR)/, $(MANDATORY) $(ADDITIONAL) $(PRINTF_SRCS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus