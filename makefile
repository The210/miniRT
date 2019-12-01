# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/16 17:26:10 by dhorvill          #+#    #+#              #
#    Updated: 2019/12/01 20:38:45 by dhorvill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

LIBFT = libft.a

SRCS = minirt.c setup_win.c sphere_ops.c vector_ops.c raytrace.c shadows.c

OBJ = $(SRC=.c:.o)

INCLUDEPATH = libft/

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	@$(CC) $(CFLAGS) -I$(INCLUDEPATH) $(INCLUDEPATH)$(LIBFT) $(SRCS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

$(LIBFT):
	@cd libft && make

clean:
	@cd libft && make clean

fclean:
	@cd libft && make fclean
	@rm -f $(NAME)

re: fclean all
