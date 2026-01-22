# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carbon-m <carbon-m@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 00:00:00 by carbon-m          #+#    #+#              #
#    Updated: 2026/01/22 13:53:14 by carbon-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CC_FLAGS = -Wall -Wextra -Werror 
MLX_FLAGS = -L$(LIB_DIR)/minilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz -O3
LIBFT_FLAGS = -L$(LIB_DIR)/libft -lft
DEBUG_FLAGS = -g3 -fsanitize=address
HEADERS = -I$(INC_DIR)

LIB_DIR = libs/
INC_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/
LOG_DIR = log/
MKDIR = mkdir -p

# Archivos de carbon (parsing)
CARBON_FILES = carbon/parsing/parse_map.c \
			carbon/parsing/parse_elements.c \
			carbon/parsing/parse_textures.c \
			carbon/parsing/parse_colors.c \
			carbon/parsing/parse_map_grid.c \
			carbon/parsing/read_file.c \
			carbon/parsing/validate_map.c \
			carbon/parsing/validate_map_borders.c \
			carbon/parsing/parse_utils.c \
			carbon/parsing/player_utils.c \
			carbon/parsing/debug_utils.c \
			carbon/parsing/debug_utils2.c

# Archivos de alcarril (motor gráfico)
ALCARRIL_FILES = alcarril/mlx_init_close/init_mlx_game.c \
			alcarril/mlx_init_close/setup_game.c \
			alcarril/mlx_init_close/init_setup_utils.c \
			alcarril/mlx_init_close/close_mlx_game.c \
			alcarril/mlx_init_close/colors.c \
			alcarril/events/keys.c \
			alcarril/events/graphic_engine_keys.c \
			alcarril/events/ambiance_keys.c \
			alcarril/events/minimap_keys.c \
			alcarril/events/player_keys.c \
			alcarril/events/mouse_keys_buttons.c \
			alcarril/moves/move_player.c \
			alcarril/moves/mouse.c \
			alcarril/render/render.c \
			alcarril/render/raycasting.c \
			alcarril/render/dda_algorith.c \
			alcarril/render/floor_celling.c \
			alcarril/render/render_textures.c \
			alcarril/render/render_minimap.c \
			alcarril/render/rays_2d.c \
			alcarril/ambiances/ambiance_configs.c \
			alcarril/ambiances/shaders_fog_blur.c \
			alcarril/ambiances/shaders.c

# Archivos puente (integración)
PUENTE_FILES = puente/bridge.c \
			puente/bridge_utils.c \
			puente/main.c

# Todos los archivos fuente
SRC_FILES = $(CARBON_FILES) $(ALCARRIL_FILES) $(PUENTE_FILES)

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT = $(LIB_DIR)/libft/libft.a
MINI_LIBX = $(LIB_DIR)/minilibx-linux/libmlx.a

all: $(LIBFT) $(MINI_LIBX) $(OBJ_DIR) $(LOG_DIR) $(NAME)

$(LIBFT): 
	make all -C libs/libft

$(MINI_LIBX):
	make all -C libs/minilibx-linux

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)

$(LOG_DIR):
	@$(MKDIR) $(LOG_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MINI_LIBX)
	$(CC) $(CC_FLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CC_FLAGS) $(HEADERS) -c $< -o $@

clean:
	make clean -C $(LIB_DIR)/libft
	make clean -C $(LIB_DIR)/minilibx-linux
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)/libft
	rm -rf $(NAME)
	rm -rf $(LOG_DIR)

re: fclean all

.PHONY: clean fclean re all
