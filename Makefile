NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -g3  -Werror -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3
MLXFLAGS = -lmlx -framework AppKit -framework OpenGL
RM = rm -f

SRC_FILES =	./src/main.c \
			./src/utils.c \
			./src/parsing/get_textures.c \
			./src/parsing/parsing_colors.c \
			./src/parsing/main_parsing.c \
			./src/parsing/parsing_doubles.c \
			./src/parsing/parsing_elements.c \
			./src/init_ray/init_mlx.c \
			./src/init_ray/raycasting.c \


HEADER = includes

OBJS = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "----------------"
	@echo "| Compiling... |"
	@$(MAKE) -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/*.o $(MLXFLAGS)
	@echo "|  Done ! 🧊   |"
	@echo "----------------"

%.o: %.c
	@$(CC) $(CFLAGS) -I$(HEADER) -c -o $@ $< -I. -Ilibft

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C libft clean
	@echo "... cleaned !"

fclean: clean
	@$(MAKE) -C libft fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
