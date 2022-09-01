# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 19:18:15 by sarchoi           #+#    #+#              #
#    Updated: 2022/09/01 17:03:39 by sarchoi          ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re $(LIBFT) $(NAME)

NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_ROOT = main.c \
			map.c \
			map_parse.c \
			map_parse_read_colors.c \
			map_parse_read_map.c \
			map_parse_read_textures.c \
			map_validate.c \
			map_validate_char.c \
			map_validate_walls.c \
			map_validate_empty.c \
			get_map_array.c \
			graphic_init.c \
			draw_frame.c \
			find_map_start_line.c \
			free.c \
			put_screen.c \
			put_minimap_floor.c \
			put_minimap_tiles.c \
			put_minimap_line.c \
			put_minimap_player.c \
			put_minimap_ray.c \
			mouse_hook.c \
			key_hook.c \
			calc_rotated_vector.c \
			player.c \
			init_player.c \
			bres_algo.c \
			set_fire_texture.c
SRCS_UTIL = global.c \
			draw.c \
			draw_pixel.c \
			mlx_image.c \
			put_image.c \
			get_image.c \
			exit.c \
			dda_algo.c \
			print.c
SRCS = $(addprefix ./src/, $(SRCS_ROOT)) \
		$(addprefix ./src/utils/, $(SRCS_UTIL))
SRCS_BONUS = $(addprefix ./src_bonus/, $(SRCS_ROOT:.c=_bonus.c)) \
			$(addprefix ./src_bonus/utils/, $(SRCS_UTIL:.c=_bonus.c))

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

MLX = minilibx
MLX_FLAGS = -L libs/minilibx -lmlx -framework OpenGl -framework AppKit

LIBFT = libft
LIBFT_FLAGS = -L libs/libft -lft

SRCS_GNL = libs/get_next_line/get_next_line_utils.c \
		   libs/get_next_line/get_next_line.c
OBJS_GNL = $(SRCS_GNL:.c=.o)
GNL = get_next_line

INC_FLAGS = -I includes -I libs/$(LIBFT) -I libs/$(GNL) -I libs/$(MLX)

green:=$(shell tput setaf 2)
reset:=$(shell tput sgr0)

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS) $(OBJS_GNL)
	$(info $(green)<MAKE> NAME$(reset))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAGS) $(MLX_FLAGS)
	install_name_tool -change libmlx.dylib $(CURDIR)/libs/$(MLX)/libmlx.dylib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)
	$(info $(green)<MAKE> $(<) -> $(@)$(reset))

$(LIBFT):
	make all bonus --directory=libs/$(LIBFT)

$(MLX):
	make --directory=libs/$(MLX)

bonus: $(OBJS_BONUS) $(OBJS_GNL)
	$(info $(green)<MAKE> bonus$(reset))
	make $(LIBFT)
	make $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBFT_FLAGS) $(MLX_FLAGS)
	install_name_tool -change libmlx.dylib $(CURDIR)/libs/$(MLX)/libmlx.dylib $(NAME)

clean:
	@make clean --directory=libs/$(LIBFT)
	$(info $(green)<MAKE> Libft - clean$(reset))
	@make clean --directory=libs/$(MLX)
	$(info $(green)<MAKE> MinilibX - clean$(reset))
	rm -f $(OBJS) $(OBJS_GNL)
	$(info $(green)<MAKE> clean$(reset))

fclean: clean
	make fclean --directory=libs/$(LIBFT)
	$(info $(green)<MAKE> Libft - fclean$(reset))
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	rm -rf libs/minilibx/*.swiftsourceinfo
	$(info $(green)<MAKE> fclean$(reset))

re: fclean all
	$(info $(red)<MAKE> re$(reset))
