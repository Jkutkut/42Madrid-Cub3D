## ---   ---   ---         ---   ---   --- ###
#             PROJECT COMPILATION             #
### ---   ---   ---         ---   ---   --- ###

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra# -g3 -fsanitize=address

### ---   ---   ---         ---   ---   --- ###
#               PROJECT PATHS                 #
### ---   ---   ---         ---   ---   --- ###

INCLUDE				= -I include -I libft/include

SRCS_PATH			= src/
LIBFT_PATH			= libft/
LIBFT				= $(LIBFT_PATH)libft.a
LIBFT_REPO			= $(LIBFT_PATH)Makefile
MLX_PATH			= mlx

ifeq ($(shell uname -s), Darwin)
	#CFLAGS		+= -l $(MLX_PATH)
	CFLAGS		+= -I $(MLX_PATH)
	MLXFLAGS	= -L $(MLX_PATH) -l $(MLX_PATH) -framework OpenGL -framework AppKit
	# MLXFLAGS	= -L $(MLX_PATH) -I $(MLX_PATH) -framework OpenGL -framework AppKit
endif

### ---   ---   ---         ---   ---   --- ###
#               PROJECT FILES                 #
### ---   ---   ---         ---   ---   --- ###

NAME		= cub3D

SRC_FILES	= 	main.c \
				model/vector.c

SRC_OBJS 	= $(SRC_FILES:%.c=bin/%.o)

### ---   ---   ---         ---   ---   --- ###
#              COLORS & EXTRAS :)             #
### ---   ---   ---         ---   ---   --- ###

NC			=	\033[0m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
LRED		=	\033[1;31m
LGREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
LBLUE		=	\033[1;34m
TITLE		=	\033[38;5;33m

### ---   ---   ---         ---   ---   --- ###
#                     RULES                   #
### ---   ---   ---         ---   ---   --- ###

.PHONY: all re clean fclean norm todo TODO execute

all: $(NAME)

$(NAME): $(LIBFT) $(SRC_OBJS)
	@echo "\n${TITLE}Compiling${NC} ${YELLOW}$(NAME)${NC} into ${YELLOW}$(NAME)${NC}\c"
	@$(CC) $(CFLAGS) $(INCLUDE) $(MLXFLAGS) $(SRC_OBJS) $(LIBFT) -o $(NAME)
	@echo " ${GREEN}[OK]${NC}\n"

$(LIBFT): $(LIBFT_REPO)
	@make -C $(LIBFT_PATH)

# TODO debug
$(LIBFT_REPO):
	#git clone git@github.com:jkutkut/42madrid-libft libft
	@git submodule update --init --recursive

bin:
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $@)/model

bin/%.o: src/%.c bin
	@echo "$(TITLE)Compiling${NC} $< -> $@\c"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo " ${GREEN}[OK]${NC}"

clean: $(LIBFT_REPO)
	@echo "- ${RED}Removing${NC} binary directory"
	@rm -rf $(BIN)
	@echo "- ${RED}Removing${NC} libft directory"
	@make -C $(LIBFT_PATH) fclean
	@# TODO mlx

fclean: clean
	@echo "- ${RED}Removing${NC} $(NAME)"
	@rm -f $(NAME)
	@echo "Project ${YELLOW}$(NAME) ${GREEN}clean${NC}.\n"
	@rm -f model_test

re: fclean all

### ---   ---   ---         ---   ---   --- ###
#                 Development                 #
### ---   ---   ---         ---   ---   --- ###

norm:
	@norminette $(SRC_FILES:%=$(SRCS_PATH)%) include | sed "s/src/\\`echo '\n\r'`/g"

norm_docker:
	docker run --rm -v $(PWD):/docker jkutkut/docker4norminette:latest $(SRC_FILES:%=$(SRCS_PATH)%) include | sed "s/src/\\`echo '\n\r'`/g"

todo:
	@cat $(SRC_FILES:%=$(SRCS_PATH)%) | grep '//\stodo:.*' -ioh --color=never

TODO:
	@echo "*****************************************"
	@grep "TODO" -nr -i --exclude-dir=".git" .
	@echo "*****************************************"

MODEL_SRCS =	model/test_vector.c \
				model/vector.c

MODEL_OBJS = $(MODEL_SRCS:%.c=bin/%.o)

model_test: $(MODEL_OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(MODEL_OBJS) -o model_test
