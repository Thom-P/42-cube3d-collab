# COLOURS

_END		=	\e[0m
_BOLD		=	\e[1m
_DIM		=	\e[2m
_UNDER		=	\e[4m
_REV		=	\e[7m

_GREY		=	\e[30m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_BLUE		=	\e[34m
_PURPLE		=	\e[35m
_CYAN		=	\e[36m
_WHITE		=	\e[37m

_IGREY		=	\e[40m
_IRED		=	\e[41m
_IGREEN		=	\e[42m
_IYELLOW	=	\e[43m
_IBLUE		=	\e[44m
_IPURPLE	=	\e[45m
_ICYAN		=	\e[46m
_IWHITE		=	\e[47m

_MOFF		=	\e[?25l
_MON		=	\e[?25h
_MUP		=	\e[1A
_ERASE		=	\e[K

#NB = $(shell find . -type f | grep .c | grep src/ | wc -l)
CNT = 1

NAME = cub3d

OBJ_DIR = objs/
INC_DIR = include/
SRC_DIR = src/

LIBFT = libft/
MLX = minilibx_macos

FRAMEWORKS = -framework OpenGL -framework AppKit
INCS = -I$(INC_DIR) -I$(LIBFT) -I$(MLX) -I$(LIBFT)/get_next_line/ -I$(LIBFT)/printf/
LIBS = -L$(LIBFT) -lft -L$(MLX) -lmlx

SRC =	draw_2D_scene.c \
		draw_3D_scene.c \
		draw_segment.c \
		hooks.c \
		main.c \
		minimap.c \
		raycast.c \
		update_and_render.c \
		utils.c \
		doors.c \
		parsing/colors.c \
		parsing/get_textures.c \
		parsing/helpers.c \
		parsing/load_textures.c \
		parsing/map_check.c \
		parsing/map_check2.c \
		parsing/name_checks.c \
		parsing/parse.c \
		sprite.c

OBJ := $(SRC:%.c=%.o)
DEP := $(SRC:%.c=%.d)

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))
DEPS = $(addprefix $(OBJ_DIR), $(DEP))

CCFLAGS = -Wall -Wextra -Werror -Wconversion

all: libft mlx $(NAME)

$(NAME): $(SRCS) $(OBJ_DIR) $(OBJS)
	@printf "\n\n$(_BOLD)$(_WHITE)cub3d ready$(_END)\n"
	@gcc -O2 $(CCFLAGS) $(OBJS) $(LIBS) $(FRAMEWORKS) -o $(NAME)
	@printf "$(_BOLD)$(_GREEN)OK! $(_END)$(_DIM)$(_WHITE)(./$(NAME))$(_END)\n\n"

debug: libft mlx $(SRCS) $(OBJ_DIR) $(OBJS)
	gcc -O0 $(CCFLAGS) -fsanitize=address -g3 $(OBJS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

-include $(DEPS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@gcc $(CCFLAGS) -MMD $(INCS) $< -c -o $@
	@printf "$(_ERASE)\r"
	@printf "$(_WHITE)$<$(_END)\n"
	@for i in $$(seq 1 $(CNT)); \
	do \
		printf "$(_BOLD)$(_GREEN)█$(_END)"; \
	done
	$(eval CNT=$(shell echo $$(($(CNT)+1))))
	@printf "\r$(_MUP)"

clean:
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)$(NAME)$(_WHITE) objects and dependencies$(_END)\n"
	@rm -f $(OBJS)
	@rm -f $(DEPS)
	@rm -rf $(OBJ_DIR)
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)libft$(_WHITE) objects$(_END)\n"
	@make clean -C $(LIBFT)
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)mlx$(_WHITE) objects$(_END)\n"
	@make clean -C $(MLX)

fclean: clean
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)$(NAME)$(_WHITE) (./$(NAME))$(_END)\n"
	@rm -f $(NAME)
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)libft.a$(_WHITE) (./$(LIBFT)libft.a)$(_END)\n"
	@rm -f $(LIBFT)libft.a
	@printf "$(_BOLD)$(_WHITE)Removing $(_RED)libmlx.a$(_WHITE) (./$(MLX)libmlx.a)$(_END)\n"
	@rm -f $(MLX)libmlx.a

re: fclean all

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/parsing/

libft:
	@make -C $(LIBFT)

mlx:
	@printf "$(_BOLD)$(_WHITE)compiling libmlx$(_END)\n"
	@make -C $(MLX)
	@printf "$(_BOLD)$(_GREEN)OK! $(_END)$(_DIM)$(_WHITE)(./libmlx.a)$(_END)\n\n"

.PHONY: libft
