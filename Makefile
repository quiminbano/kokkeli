# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 14:43:17 by corellan          #+#    #+#              #
#    Updated: 2023/01/03 11:03:14 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = main.c pipex.c pipex_cont.c pipex_utils.c pipex_error.c

SRC_GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OUT = main.o pipex.o pipex_cont.o pipex_utils.o pipex_error.o

GNL_OUT = get_next_line.o get_next_line_utils.o

FLAGS = -Wall -Wextra -Werror

LIB_GNL = get_next_line

PF = -Lft_printf -lftprintf

CC = cc

all: $(NAME)

$(NAME): $(OUT) $(GNL_OUT)
		$(MAKE) -C ./ft_printf
		$(CC) $(FLAGS) -I. -c $(SRC)
		$(CC) $(FLAGS) $(OUT) $(GNL_OUT) $(PF) -o $(NAME)

$(GNL_OUT):
		$(CC) $(FLAGS) -I$(LIB_GNL) -c $(SRC_GNL)

clean:
		$(MAKE) clean -C ./ft_printf
		rm -f $(OUT) $(GNL_OUT)

fclean: clean
		$(MAKE) fclean -C ./ft_printf
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re