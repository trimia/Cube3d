NAME = cub3d
CC = gcc
SRC = main.c read_file.c utility.c init.c check.c check_extra.c 
OBJS = $(SRC:.c=.o)
FLAG = -g -Wall -Werror -Wextra
LIB = ./libft/libft.a
MLX		=	./libmlx.dylib

%.o: %.c
			$(CC) ${FLAG} -g -c $< -o $@ 

all: $(NAME)

$(NAME):	$(OBJS)
			@(test -f $(MLX)  && echo "\033[32mMLX already built\033[0m") || (make -C ./minilibx && mv minilibx/libmlx.dylib .)
			$(CC) $(FLAG) -o $(NAME) $(LIB) $(OBJS) $(MLX)
			@(echo "\033[32mSO_LONG>> Compiled\033[0m")
# $(NAME):
# 	gcc $(FLAG) $(SRC) $(MLX) $(LIB) -o $(NAME)

$(LIB):
	@$(MAKE) -C ./libft

# $(NAME): $(LIB) $(OBJS)
# 	$(CC) $(FLAG) $(OBJS) $(MLXFLAGS) $(LIB) -o $(NAME) 
# $(CC) $(FLAG) $(OBJS) $(LIB) $(MLX) $(MLXFLAGS) -o $(NAME) 

clean:
	rm -rf $(OBJS)

fclean: clean
		rm -f $(NAME)


re: fclean all