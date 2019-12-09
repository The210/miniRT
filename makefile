# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ede-thom <ede-thom@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 17:26:10 by dhorvill          #+#    #+#              #
#    Updated: 2019/12/08 17:16:49 by ede-thom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	src/minirt.c\
				src/setup_win.c\
				src/sphere_ops.c\
				src/vector_ops.c\
				src/raytrace.c\
				src/shadows.c\
				src/reflection.c\
				src/color_ops.c\
				src/ft_atof.c\
				src/error.c\
				src/parsing.c


MKDIR_P	=		mkdir -p
RM			=	rm -f

NAME		=	miniRT

# **************************************************************************** #

# Directories
OBJ_DIR		=	obj
INC_DIR		=	include
# **************************************************************************** #

# LIBFT
LFT_NAME	=	libft.a
LFT_PATH	=	./libft
LFT_LIB		=	-L $(LFT_PATH) -lft
LFT_INC		=	-I $(LFT_PATH)
LFT_RULE	=	$(LFT_PATH)/$(LFT_NAME)
# **************************************************************************** #

OBJS		=	$(pathsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))
LIB			=	$(LFT_LIB) $(LSDL_LIB) -lmlx -framework OpenGL -framework AppKit
INC			=	-I $(INC_DIR) $(LFT_INC) $(LSDL_INC)

# COLORS
RED			=	\033[0;31m
GREEN		= 	\033[0;32m
YELLOW		=	\033[0;33m
BLUE		=	\033[0;34m
MAGENTA		=	\033[0;35m
CYAN		=	\033[0;36m
RESET		=	\033[0m
# **************************************************************************** #
CFLAGS		=	-Wall -Wextra -Werror

CC			=	gcc


all:		${NAME}

$(NAME):		$(OBJS) $(LFT_RULE)
				@printf "$(CYAN)Done creating $(NAME) object files!\n$(RESET)"
				@$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIB) 
				@echo "$(CYAN)Created $(GREEN)$(NAME)$(CYAN)!! $(RESET)"

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INC_DIR)/
				@$(MKDIR_P) $(OBJ_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@ $(INC) $(LIB)
				@printf "$(CYAN)Compiling $(MAGENTA)$<$(RESET)\r"

$(LFT_RULE):
				@make -C $(LFT_PATH)

clean: 
				@${RM} ${OBJS}
				@echo "$(CYAN)TIDY UP $(RED)pls$(RESET)"

fclean:			clean
				@${RM} ${NAME}
				@echo "$(CYAN)Everything is $(RED)c $(YELLOW)l $(GREEN)e $(CYAN)a $(MAGENTA)n $(RESET)"

re:				fclean all

.PHONY:	all clean fclean test re