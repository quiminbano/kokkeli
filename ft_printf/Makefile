# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corellan <corellan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 13:33:33 by corellan          #+#    #+#              #
#    Updated: 2022/12/16 11:42:09 by corellan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_print_address.c ft_print_hex_u.c ft_print_hex.c ft_printf.c \
ft_uitoa.c ft_writer.c

OUT = ft_print_address.o ft_print_hex_u.o ft_print_hex.o ft_printf.o \
ft_uitoa.o ft_writer.o

FLAGS = -Wall -Wextra -Werror

LIB = ft_printf.h

CC = cc

all: $(NAME)

$(NAME): $(OUT)
		$(MAKE) -C ./../libft
		cp ../libft/libft.a .
		mv libft.a libftprintf.a
		$(CC) -c $(FLAGS) -I$(LIB) $(SRC)
		ar rc $(NAME) $(OUT)
		ranlib $(NAME)

clean:
		$(MAKE) clean -C ./../libft
		rm -f $(OUT)

fclean: clean
		$(MAKE) fclean -C ./../libft
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re