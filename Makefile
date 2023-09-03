# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgutak <dgutak@student.42vienna.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/31 17:55:20 by dgutak            #+#    #+#              #
#    Updated: 2023/08/30 13:21:01 by dgutak           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux 
LDFLAGS = -L./libft -lft

NAME = pipex
LIBFT	=	./libft/libft.a
SRCS = main.c childparent.c

OBJS = $(SRCS:.c=.o)


all: $(NAME)
	rm -f $(OBJS)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJS) $(LDFLAGS) -g

.c.o:
	cc $(CFLAGS) -c $< -o $(<:.c=.o) -I ./include


clean:
	rm -f $(OBJS)


fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
