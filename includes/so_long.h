/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:39:36 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 04:06:30 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "../libs/libft_light/libft.h"
# include "../libs/minilibx/mlx.h"

# define PATH_WALL "./sprite_files/wall.xpm"
# define PATH_FLOOR "./sprite_files/floor.xpm"
# define PATH_EXIT "./sprite_files/exit.xpm"
# define PATH_OBJ "./sprite_files/obj.xpm"
# define PATH_PLAYER "./sprite_files/player.xpm"
# define PATH_ENEMY "./sprite_files/enemy.xpm"

typedef enum e_sides
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_sides;

typedef struct s_spec
{
	char	token;
	int		qtd;
	int		init_qtd;
	size_t	y;
	size_t	x;
	size_t	init_y;
	size_t	init_x;
	size_t	step_counter;
}			t_spec;

typedef struct s_components
{
	char	wall;
	char	empty;
	char	enemy;
	t_spec	player;
	t_spec	exit;
	t_spec	obj;
}			t_components;

typedef struct s_map
{
	char			**fill;
	char			**backup;
	size_t			row;
	size_t			col;
	t_components	comp;
}					t_map;

typedef struct s_gui
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*win_title;
	int		bpp;
	t_map	*map;
}			t_gui;

int		ft_map_mngmt(const char **argv);
int		ft_error(char *message);
int		ft_warning(char *message);
int		ft_validate_map(t_map *map);
int		ft_build_game(t_map *map);
void	ft_render_map(t_gui *gui, int i, int j, int s);
void	ft_render_step(t_gui *gui);
void	ft_move_x(t_gui *gui, t_sides side);
void	ft_move_y(t_gui *gui, t_sides side);
int		ft_reset_game(t_map *map, t_components *comp);
void	ft_free_map(char **map);

#endif
