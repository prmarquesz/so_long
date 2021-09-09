/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 03:34:00 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 03:34:06 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	ft_key_hook(int keycode, t_gui	*gui);
static int	ft_expose(t_gui	*gui);
static int	ft_close_win(t_gui	*gui);

/**
 * @brief This function is responsible for building the window and 
 * triggers the game's rendering functions.
 * @param map The map to be played.
 * @return 1 if the game was built successfully, 0 otherwise.
*/
int	ft_build_game(t_map *map)
{
	t_gui	gui;

	gui.win_title = "So Long";
	gui.bpp = 40;
	gui.map = map;
	gui.mlx = mlx_init();
	gui.win = mlx_new_window(gui.mlx, map->col * gui.bpp,
			map->row * gui.bpp, gui.win_title);
	mlx_expose_hook(gui.win, ft_expose, &gui);
	mlx_hook(gui.win, 17, 0, ft_close_win, &gui);
	mlx_key_hook(gui.win, ft_key_hook, &gui);
	ft_render_map(&gui, 0, 0, 0);
	ft_render_step(&gui);
	mlx_loop(gui.mlx);
	return (1);
}

/**
 * @brief This function is responsible for keeping the game rendered
 * in the window when it is minimized.
 * @param gui The gui (graphical user interface) structure.
*/
static int	ft_expose(t_gui	*gui)
{
	ft_render_map(gui, 0, 0, 0);
	ft_render_step(gui);
	return (1);
}

/**
 * @brief This function is responsible for closing the window.
 * @param gui The gui (graphical user interface) structure.
 * @return 1 if the window was closed successfully, 0 otherwise.
*/
static int	ft_close_win(t_gui	*gui)
{
	mlx_destroy_window(gui->mlx, gui->win);
	exit(0);
	return (1);
}

/**
 * @brief This function is responsible for handling the keyboard events.
 * @param keycode The keycode of the pressed key.
 * @param gui The gui (graphical user interface) structure.
 * @return 1 if the key was handled, 0 otherwise.
*/
static int	ft_key_hook(int keycode, t_gui	*gui)
{
	printf("Hello from key_hook!\n");
	printf("%c\n", keycode);
	printf("%d\n\n", keycode);
	if (keycode == 65307)
		ft_close_win(gui);
	else if ((char)keycode == 'w')
		ft_move_y(gui, UP);
	else if ((char)keycode == 's')
		ft_move_y(gui, DOWN);
	else if ((char)keycode == 'a')
		ft_move_x(gui, LEFT);
	else if ((char)keycode == 'd')
		ft_move_x(gui, RIGHT);
	ft_render_map(gui, 0, 0, 0);
	ft_render_step(gui);
	return (1);
}
