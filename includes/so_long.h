/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:39:36 by proberto          #+#    #+#             */
/*   Updated: 2021/09/18 14:38:40 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "../libs/libft_light/libft.h"
# include "../libs/minilibx/mlx.h"

# define UP 'w'
# define DOWN 's'
# define LEFT 'a'
# define RIGHT 'd'
# define PATH_WALL "./sprite_files/wall.xpm"
# define PATH_FLOOR "./sprite_files/floor.xpm"
# define PATH_EXIT "./sprite_files/exit.xpm"
# define PATH_OBJ "./sprite_files/obj.xpm"
# define PATH_ENEMY "./sprite_files/enemy.xpm"
# define PATH_PLAYER_DOWN "./sprite_files/player_down.xpm"
# define PATH_PLAYER_DOWN1 "./sprite_files/player_down1.xpm"
# define PATH_PLAYER_DOWN2 "./sprite_files/player_down2.xpm"
# define PATH_PLAYER_UP "./sprite_files/player_up.xpm"
# define PATH_PLAYER_UP1 "./sprite_files/player_up1.xpm"
# define PATH_PLAYER_UP2 "./sprite_files/player_up2.xpm"
# define PATH_PLAYER_RIGHT "./sprite_files/player_right.xpm"
# define PATH_PLAYER_RIGHT1 "./sprite_files/player_right1.xpm"
# define PATH_PLAYER_RIGHT2 "./sprite_files/player_right2.xpm"
# define PATH_PLAYER_LEFT "./sprite_files/player_left.xpm"
# define PATH_PLAYER_LEFT1 "./sprite_files/player_left1.xpm"
# define PATH_PLAYER_LEFT2 "./sprite_files/player_left2.xpm"
# define PATH_PLAYER_WIN "./sprite_files/win.xpm"

typedef struct s_spec
{
	char	token;
	char	*sprite_path;
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
	int		end_game;
	t_map	*map;
}			t_gui;

int		ft_map_mngmt(const char **argv);
int		ft_error(char *message);
int		ft_warning(char *message);
int		ft_validate_map(t_map *map);
int		ft_build_game(t_map *map);
void	ft_render_game(t_gui *gui);
int		ft_render_you_win(t_gui *gui, int x, int y);
int		ft_render_you_lost(t_gui *gui);
int		ft_move_x(t_gui *gui, char side);
int		ft_move_y(t_gui *gui, char side);
void	ft_stop_player(t_gui *gui, char side);
int		ft_enemy_patrols(t_gui *gui);
char	ft_try_up(t_gui *gui, int i, int j);
char	ft_try_down(t_gui *gui, int i, int j);
char	ft_try_left(t_gui *gui, int i, int j);
char	ft_try_right(t_gui *gui, int i, int *j);
int		ft_reset_game(t_gui *gui);
void	ft_free_map(char **map);

#endif
