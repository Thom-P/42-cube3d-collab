SRCS	= ft_atoi.c		ft_isalnum.c		ft_isdigit.c		ft_memcmp.c \
		  ft_memset.c	ft_strlcat.c		ft_strncmp.c		ft_tolower.c \
		  ft_bzero.c	ft_isalpha.c		ft_isprint.c		ft_memcpy.c \
		  ft_strchr.c	ft_strlcpy.c		ft_strnstr.c		ft_toupper.c \
		  ft_calloc.c	ft_isascii.c		ft_memchr.c			ft_memmove.c \
		  ft_strdup.c	ft_strlen.c			ft_strrchr.c		ft_putendl_fd.c \
		  ft_striteri.c	ft_strlen.c			ft_putnbr_fd.c		ft_strjoin.c \
		  ft_strmapi.c	ft_itoa.c			ft_putstr_fd.c		ft_strlcat.c \
		  ft_strtrim.c	ft_putchar_fd.c		ft_split.c			ft_strlcpy.c \
		  ft_substr.c	ft_lstnew.c			ft_lstadd_front.c	ft_lstsize.c \
		  ft_lstlast.c  ft_lstadd_back.c	ft_lstdelone.c		ft_lstclear.c \
		  ft_lstiter.c	ft_lstmap.c \
		  ./get_next_line/get_next_line.c   ./get_next_line/get_next_line_utils.c \
		  ./printf/formatting.c				./printf/print_decimal.c \
		  ./printf/ft_litoa.c				./printf/ft_ultoa_base.c \
		  ./printf/print_hex.c				./printf/ft_printf.c \
		  ./printf/parsing.c				./printf/print_str_char.c \

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

CC	= gcc
RM	= rm -f 

CFLAGS	= -Wall -Wextra -Werror -I./ -I./get_next_line/ -I./printf/

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar -rcs ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
