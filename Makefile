# ************************************************************************** */
#                                                                            */
#                                                        :::      ::::::::   */
#   Makefile                                           :+:      :+:    :+:   */
#                                                    +:+ +:+         +:+     */
#   By: iiskakov <iiskakov@student.42.fr>          +#+  +:+       +#+        */
#                                                +#+#+#+#+#+   +#+           */
#   Created: 2019/07/05 08:43:04 by iiskakov          #+#    #+#             */
#   Updated: 2019/07/05 11:32:25 by iiskakov         ###   ########.fr       */
#                                                                            */
# ************************************************************************** */

.PHONY: all, $(NAME), clean, fclean, re

NAME = fdf

NOC=\033[0m
OKC=\033[32m
ERC=\033[31m
WAC=\033[33m

cc = gcc
C_FLAGS = -Wall -Wextra -Werror -O2
FRAM = -L minilibx -I minilibx -lmlx -framework OpenGL -framework AppKit 
# FRAM = -framework OpenGL -framework AppKit minilibx/libmlx.a


OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = fdf.h
SRC_NAME = main.c graphics.c scene.c keys.c projection.c parse.c  

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		@echo
		@make -C $(LFT_PATH)
		@$(CC) -o $(NAME) $(FRAM) -L $(LFT_PATH) -lft $^ -o $@ 
		@echo "$(OKC)FDF:\t\tFDF READY$(NOC)"
		@echo "-----> ಠ_ಠ"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<
		@echo -n =

clean:
		@make -C $(LFT_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "$(WAC)FDF:\t\tRemoving OBJ path: ./obj/$(NOC)"

fclean: clean
		@make -C $(LFT_PATH) fclean
		@rm -f $(NAME)
		@echo "$(WAC)FDF:\t\tRemoving fdf executables$(NOC)"

re: fclean all
