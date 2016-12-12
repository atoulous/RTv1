# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoulous <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/06/17 21:56:41 by atoulous          #+#    #+#              #
#    Updated: 2016/12/12 17:16:36 by atoulous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC = Sources/calc_forms.c Sources/events.c Sources/exit_free.c \
	  Sources/init_rtv1.c Sources/launch_rtv1.c Sources/parse_doc.c \
	  Sources/parse_doc2.c Sources/parse_doc3.c Sources/rtv1.c \
	  Sources/vector.c Sources/vector2.c

OBJ = $(SRC:.c=.o)

CF = gcc -Wall -Werror -Wextra

LIBS = -LLibs/libft/ -LLibs/minilibx_macos/

$(NAME): $(OBJ)
	@echo
	@make -C Libs/libft
	@make -C Libs/minilibx_macos
	@$(CF) $(LIBS) -lft -lmlx -framework OpenGL -framework AppKit -o $@ $^
	@echo "\033[32mrtv1 well compiled\033[0m"
	@echo

all: $(NAME)

%.o: %.c
	@$(CF) -o $@ -c $<

.PHONY: fclean

clean:
	@make clean -C Libs/libft
	@make clean -C Libs/minilibx_macos
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C Libs/libft
	@rm -f $(NAME)

re: fclean all
