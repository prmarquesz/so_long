# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/14 00:24:07 by proberto          #+#    #+#              #
#    Updated: 2021/09/09 04:15:52 by proberto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_LIBFT = libs/libft_light
PATH_MLX = libs/minilibx
PATH_SRC = src

NAME = so_long
LIBFT = $(PATH_LIBFT)/libft.a
MLX = $(PATH_MLX)/libmlx.a
SRC = $(PATH_SRC)/so_long.c $(addprefix $(PATH_SRC)/utils/, \
ft_map_mngmt.c ft_errors_warnings.c ft_validate_map.c ft_build_game.c \
ft_render.c ft_move.c ft_reset_game.c ft_free.c)
OBJS = $(SRC:.c=.o)
MAP = map_files/map2.ber
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
MLXFLAGS = -Imlx -lX11 -lXext
RM = rm -f

all:	$(NAME)
	
$(NAME):	$(OBJS) $(LIBFT) $(MLX)
	@$(CC) -g $(CFLAGS) $(SRC) $(LIBFT) $(MLX) $(MLXFLAGS) -o $@

%.o:	%.c
	@$(CC) -g $(CFLAGS) -c $< -o $@

$(LIBFT):	
	@$(MAKE) -C $(PATH_LIBFT)

$(MLX):	
	@$(MAKE) -C $(PATH_MLX)

exe:	
	@./$(NAME) $(MAP)

norm:	
	norminette includes/
	norminette libs/libft_light/
	norminette src/

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C $(PATH_LIBFT)
#	@$(MAKE) clean -C $(PATH_MLX)


fclean:	clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(PATH_LIBFT)
#	@$(MAKE) fclean -C $(PATH_MLX)

re:	fclean all

.PHONY:	all clean fclean re
