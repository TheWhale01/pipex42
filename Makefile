CC=gcc
BIN_DIR=bin/
OBJ_DIR=obj/
SRC_DIR=src/
LIBFT_DIR=libft/
INCLUDES=includes/
CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES)
NAME=$(BIN_DIR)pipex
NAME_BONUS=$(BIN_DIR)pipex_bonus

CFILES=$(addprefix $(SRC_DIR), main.c utils.c pipex.c)
CFILES_BONUS=$(addprefix $(SRC_DIR)bonus/, main_bonus.c pipex_bonus.c ../utils.c)
OBJS=$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(CFILES))
OBJS_BONUS=$(patsubst $(SRC_DIR)bonus/%.c, $(OBJ_DIR)bonus/%.o, $(CFILES_BONUS))

$(OBJ_DIR)bonus/%.o: $(SRC_DIR)bonus/%.C
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$(dir $@)" ]; then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@if [ ! -d "./$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L ./$(LIBFT_DIR)bin/ -lft

all: $(NAME)

bonus: $(NAME) $(OBJS_BONUS)
	@if [ ! -d "./$(BIN_DIR)" ]; then mkdir $(dir $@); fi
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME_BONUS) -L ./$(LIBFT_DIR)bin/ -lft

debug: CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -g
debug: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

sanitize:CFLAGS=-Wall -Wextra -Werror -I $(INCLUDES) -fsanitize=address
sanitize: $(NAME)

re: fclean all

re_bonus: fclean bonus

re_debug: fclean debug

re_sanitize: fclean sanitize

.PHONY: all bonus debug clean fclean sanitize re_debug re_sanitize \
re_bonus