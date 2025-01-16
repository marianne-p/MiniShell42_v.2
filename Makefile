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
SRC	:= main.c token.c bonus_parser.c token_split_logical.c \
		env_list_to_arr.c ft_env_unset.c ft_get_env.c ft_set_env.c \
		init_env.c print_env_list.c split_path.c \
		expand_line.c parse.c parse_redir.c \
		free.c 
OBJ_DIR	:= obj
CFLAGS	:= -Wall -Wextra -Werror -g -I./include
LIBFT_DIR	:= ./ft_libft
OBJ	:= $(SRC:%.c=$(OBJ_DIR)/%.o)
LIBFT	:= $(LIBFT_DIR)/libft_ft.a
LIB	:= -lreadline -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft_ft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $^ -o $@ $(LIB) 

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

all:	$(LIBFT) $(OBJ) $(NAME)

re:	fclean all

.PHONY:  clean fclean re all
