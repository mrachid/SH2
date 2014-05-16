# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrachid <mrachid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/13 10:47:53 by mrachid           #+#    #+#              #
#    Updated: 2014/05/16 18:52:00 by mrachid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell2

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Werror -Wextra

SRC =	shell.c \
		env.c \
		builtin1.c \
		builtin2.c \
		envtools.c \
		symbols.c \
		signal.c \
		pipex.c \
		write.c \
		gest_cmd.c \
		get_cmd.c \
		tool.c

.PHONY: clean all re fclean

all: $(NAME)

make:
	@make -C libft/

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) -L libft -lft -g

%.o : %.c
	@make -C libft/
	@gcc -g -I libft/includes/ $(FLAG) -c $^

clean:
	@make -C libft/ clean
	@/bin/rm -rf $(OBJ)

fclean: clean
	@make -C libft/ fclean
	@/bin/rm -f $(NAME)

re: fclean all

