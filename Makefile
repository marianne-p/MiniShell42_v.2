# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpihur <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 15:17:25 by mpihur            #+#    #+#              #
#    Updated: 2024/07/18 18:01:22 by mpihur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
SRC_DIR	:= src
SRC	:= main.c
OBJ_DIR	:= obj
OBJ	:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT	:= ./Libft/libft.a
LIB	:= -lreadline -I./Libft -L./Libft -lft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc -Wall -Wextra -Werror -g -c $< -o $@ 

$(NAME): $(OBJ) $(LIBFT)
	cc -Wall -Wextra -Werror -g $^ -o $@ $(LIB) 

$(LIBFT):
	make -C ./Libft

mari:	$(LIBFT)
	cc -Wall -Wextra -Werror $(M_OBJ) -o mari $(LIB) 

clean:
	rm -rf $(OBJ)
	make -C ./Libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./Libft fclean

all:	$(LIBFT) $(OBJ) $(NAME)

re:	fclean all

.PHONY:  clean fclean re all