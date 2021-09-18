# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/14 00:24:07 by proberto          #+#    #+#              #
#    Updated: 2021/09/18 16:14:13 by proberto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_INCLUDES = includes/
PATH_LIBFT = libs/libft_light
PATH_MLX = libs/minilibx
PATH_SRC = src

NAME = so_long
LIBFT = $(PATH_LIBFT)/libft.a
MLX = $(PATH_MLX)/libmlx.a
SRC = $(PATH_SRC)/so_long.c $(addprefix $(PATH_SRC)/utils/, \
ft_map_mngmt.c ft_errors_warnings.c ft_validate_map.c ft_build_game.c \
ft_render.c ft_move.c ft_enemy_patrols.c ft_try_move_enemy.c ft_reset_game.c \
ft_free.c)
OBJS = $(SRC:.c=.o)
MAP = map_files/map3.ber
CC = gcc
CFLAGS = -Wall -Werror -Wextra
MLXFLAGS = -Imlx -lX11 -lXext
RM = rm -f

all:	$(NAME)
	
$(NAME):	$(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(MLX) $(MLXFLAGS) -o $@

%.o:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):	
	@$(MAKE) -C $(PATH_LIBFT)

$(MLX):	
	@$(MAKE) -C $(PATH_MLX)

bonus:	all

exe:	
	@./$(NAME) $(MAP)

norm:	
	norminette $(PATH_INCLUDES)
	norminette $(PATH_LIBFT)
	norminette $(PATH_SRC)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C $(PATH_LIBFT)
	@$(MAKE) clean -C $(PATH_MLX)


fclean:	clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(PATH_LIBFT)

re:	fclean all

.PHONY:	all clean fclean re
