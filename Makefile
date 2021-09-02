# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/14 00:24:07 by proberto          #+#    #+#              #
#    Updated: 2021/09/01 21:15:03 by proberto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = src/so_long.a
LIBFT = libs/libft_light/libft.a
LIBFT_DIR = libs/libft_light/
SRC_DIR = src/utils/
SRC = $(addprefix $(SRC_DIR), map_mngmt.c errors_mngmt.c ft_free.c \
validate_map.c render_map.c)
OBJS = $(SRC:.c=.o)
MAIN = src/so_long.c
MAPS = map_files/map.ber
EXE = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
RM = rm -f

all:	$(NAME)
	
$(NAME):	$(OBJS) $(LIBFT)
	@cp $(LIBFT) $(NAME)
	@ar rcs $@ $(OBJS)

%.o:	%.c
	@$(CC) -g $(CFLAGS) -c $< -o $@

$(LIBFT):	
	@$(MAKE) -C $(LIBFT_DIR)

exe:	$(NAME)
	@$(CC) -g $(CFLAGS) $(MAIN) $(NAME) -o $(EXE)
	@./$(EXE) $(MAPS)

norm:	
	norminette includes/
	norminette libs/libft_light/
	norminette src/

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)


fclean:	clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re:	fclean all

.PHONY:	all clean fclean re
