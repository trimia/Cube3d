NAME = libft.a
SRCS = ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
		ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
			ft_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
				ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memcpy.c \
					ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strrchr.c \
						ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c  \
							ft_putstr_fd.c ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
								ft_error.c ft_free_matrix.c ft_isspace.c ft_check_malloc.c
OBJS = $(SRCS:.c=.o)
P_OBJ = printf/ft_utility.o printf/ft_printf.o printf/ft_char.o printf/ft_number.o
BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
				ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJS = $(BONUS:.c=.o)
FLAGS = -Wall -Wextra -Werror
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
G_OBJ = get_next_line.o get_next_line_utils.o
G_FLAG = -D BUFFER_SIZE=1

$(NAME):
		make -C printf
		gcc $(FLAGS) -c $(GNL) $(G_FLAG)
		gcc $(FLAGS) -c $(SRCS)
		ar rc $(NAME) $(OBJS) $(P_OBJ) $(G_OBJ)
		ranlib $(NAME)

bonus:
		gcc -c $(BONUS)
		ar rc $(NAME) $(BONUS_OBJS)
		ranlib $(NAME)

all: 		$(NAME)

clean: 		
			rm -f $(OBJS) $(BONUS_OBJS) $(G_OBJ)

fclean:		clean
			rm -f $(NAME)
			make fclean -C printf

re:			fclean all

.PHONY:		all clean fclean re bonus