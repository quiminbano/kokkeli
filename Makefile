# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 14:43:17 by corellan          #+#    #+#              #
#    Updated: 2022/12/19 15:44:03 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = main.c pipex.c pipex_cont.c pipex_utils.c

SRC_GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OUT = main.o pipex.o pipex_cont.o pipex_utils.o get_next_line.o \
get_next_line_utils.o

FLAGS = -Wall -Wextra -Werror

LIB = pipex.h

LIB_GNL = get_next_line/get_next_line.h

PF = ft_printf/libftprintf.a

TRASH = pipex.h.gch get_next_line/get_next_line.h.gch

CC = cc

all: $(NAME)

$(NAME):
		$(MAKE) -C ./ft_printf
		$(CC) -c $(FLAGS) $(LIB) $(SRC)
		$(CC) -c $(FLAGS) -I$(LIB_GNL) $(SRC_GNL)
		$(CC) $(FLAGS) $(OUT) $(PF) -o $(NAME)

clean:
		$(MAKE) clean -C ./ft_printf
		rm -f $(OUT) $(TRASH)

fclean: clean
		$(MAKE) fclean -C ./ft_printf
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re