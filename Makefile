# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroguszk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/28 16:30:07 by jroguszk          #+#    #+#              #
#    Updated: 2017/11/28 18:17:59 by jroguszk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = main.c matrices.c solver.c grid.c read_input.c tetro_checker.c

OBJ = $(SRC:.c=.o)

LIBFT = includes/libft.a

HEADER = -c -I lib_fillit.h

all: $(NAME)

$(OBJ): %.o: %.c
		@gcc -c -Wall -Werror -Wextra -I includes/ $< -o $@

$(LIBFT):
	@make -C includes

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(OBJ) $(LIBFT) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)
	@make -C includes clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C includes fclean

re: fclean all
