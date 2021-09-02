/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:39:36 by proberto          #+#    #+#             */
/*   Updated: 2021/09/02 01:24:15 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "../libs/libft_light/libft.h"
# include "../libs/minilibx/mlx.h"

# define COUNT 1 
# define WRITE 2

typedef struct s_map_config
{
	size_t	row;
	size_t	col;
	char	wall;
	char	empty;
	char	exit;
	char	object;
	char	player;
	char	enemy;
}			t_map_config;

int		map_mngmt(const char **argv);

#endif
