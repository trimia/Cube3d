ARCH = $(shell uname -m)
NAME= cub3d
CC = gcc
SRC = main.c read_file.c utility.c init.c check.c check_extra.c draw_utils.c draw.c movements.c gnlcube.c 
OBJS = $(SRC:.c=.o)
FLAG = -g  #-Wall -Werror -Wextra
LIB = ./libft/libft.a
MLX = ./libmlx.dylib
MLXA = ./libmlx.dylib
%.o: %.c
			$(CC) ${FLAG} -g -c $< -o $@
all: $(NAME)
$(NAME):$(OBJS)
	@(make -C minilibx clean && make -C libft fclean && echo “\033[32m Minilibix libft clean\033[0m”)
	@(make -C ./minilibx && make -C ./libft && echo “\033[32mMinilibix libft rebuilt\033[0m”) && (mv ./minilibx/libmlx.dylib .)
	$(CC) $(FLAG) -o $(NAME) $(LIB) $(OBJS) $(MLX)
	@(echo “\033[32mCube_3D>> Compiled\033[0m”)
m:
	@(test -f $(MLX)  && echo “\033[32mMLX already built\033[0m”) || (make -C ./amlx && mv amlx/libmlx.dylib .)
	$(CC) $(FLAG) -o $(NAME) $(LIB) $(OBJS) $(MLX)
	@(echo “\033[32mCube_3D>> Compiled\033[0m”)
#quando ricompili per la prima volta su m1 lancia make A che cancella tutti il file con architettura X_86 e compila in arm
A:
	@(make -C minilibx clean && make -C libft fclean && echo “\033[32m Minilibix libft clean\033[0m”)
	@(make -C ./minilibx && make -C ./libft && echo “\033[32m Minilibix libft rebuilt\033[0m”) && (mv ./minilibx/libmlx.dylib .)
	gcc $(FLAG) $(SRC) $(MLXA) $(LIB) -o $(NAME)
	@(echo “\033[32mCube_3D>> Compiled\033[0m”)
a:
	@(test -f $(MLX)  && echo “\033[32mMLX already built\033[0m”) || (make -C ./amlx && mv amlx/libmlx.dylib .)
	gcc $(FLAG) $(SRC) $(MLXA) $(LIB) -o $(NAME)
	@(echo “\033[32mCube_3D>> Compiled\033[0m”)
$(LIB):
	@$(MAKE) -C ./libft
clean:
	rm -rf $(OBJS)
fclean: clean
		rm -f $(NAME) libmlx.dylib
re: fclean all