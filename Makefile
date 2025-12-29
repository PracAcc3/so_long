NAME		:= so_long
CC		:= cc
CFLAGS		:= -Wall -Wextra -Werror

SRCS		:= main.c map.c validate.c validate_setup.c validate_counts.c \
	validate_path.c move.c utils.c draw.c close.c \
	ft_printf/ft_printf.c ft_printf/ft_hex.c ft_printf/utilities.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS		:= $(SRCS:.c=.o)

MLX_DIR		:= minilibx-linux
MLX_MK		:= makefile.gen
MLX_LIB		:= $(MLX_DIR)/libmlx.a
MLX_LDFLAGS	:= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCLUDES	:= -I. -Ift_printf -Iget_next_line -I$(MLX_DIR)

all: $(NAME)

$(MLX_LIB):
	@if [ ! -f "$(MLX_DIR)/$(MLX_MK)" ]; then \
		echo "Configuring MiniLibX..."; \
		(cd $(MLX_DIR) && ./configure); \
	fi
	$(MAKE) -C $(MLX_DIR) -f $(MLX_MK)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LDFLAGS) -o $(NAME)

%.o: %.c so_long.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
