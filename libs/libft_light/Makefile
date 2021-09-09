# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/27 13:26:13 by proberto          #+#    #+#              #
#    Updated: 2021/09/08 20:43:06 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = get_next_line.c get_next_line_utils.c ft_strlen.c ft_strnstr.c \
ft_memchr.c ft_itoa.c
OBJS = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f

all:	$(NAME)
	
$(NAME):	$(OBJS)
	@ar rcs $@ $(OBJS)

%.o:	%.c
	@$(CC) -g $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)

re:	clean all

.PHONY:	all clean fclean re
