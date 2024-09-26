NAME = cub3d

CC = cc
CFLAGS = -Werror -Wall -Wextra -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3
MLXFLAGS = -lmlx -framework AppKit -framework OpenGL
RM = rm -f

SRC_FILES = ./src/parsing/check_map.c \
			./src/parsing/get_colors.c \
			./src/parsing/get_textures.c \
			./src/parsing/parsing_colors.c \
			./src/parsing/main_parsing.c \
			./src/parsing/parsing_doubles.c \
			./src/parsing/parsing_elements.c \
			./src/parsing/parsing_floating.c \
			./src/parsing/parsing_map.c \
			./src/parsing/parsing_textures.c \
			./src/raycasting/init_mlx.c \
			./src/raycasting/raycasting.c \
			./src/raycasting/utils.c \
			./src/main.c \
			./src/utils.c \

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
