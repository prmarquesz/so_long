/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:13:19 by proberto          #+#    #+#             */
/*   Updated: 2021/09/10 17:53:29 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	ft_render_map(t_gui *gui, int i, int j, int s);
static void	ft_render_step(t_gui *gui);

/**
 * @brief Render the game map.
 * @details Triggers the render map and render step functions,
 * (if game is not over).
 * @param gui The gui (graphical user interface) structure.
 * @return void.
*/
void	ft_render_game(t_gui *gui)
{
	if (gui->end_game)
		return ;
	ft_render_map(gui, 0, 0, 0);
	ft_render_step(gui);
}

/**
 * @brief Render the win game screen.
 * @param gui The gui (graphical user interface) structure.
 * @param x The position where the win image will be rendered on the x axis.
 * @param y The position where the win image will be rendered on the y axis.
 * @return 0 to force the game to restart.
*/
int	ft_render_you_win(t_gui *gui, int x, int y)
{
	int		width;
	int		height;

	width = 0;
	height = 0;
	gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_PLAYER_WIN,
			&width, &height);
	mlx_put_image_to_window(gui->mlx, gui->win, gui->img,
		x * gui->bpp, y * gui->bpp);
	mlx_destroy_image(gui->mlx, gui->img);
	gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_FLOOR, &width, &height);
	mlx_put_image_to_window(gui->mlx, gui->win, gui->img,
		gui->map->comp.player.x * gui->bpp, gui->map->comp.player.y * gui->bpp);
	mlx_destroy_image(gui->mlx, gui->img);
	mlx_string_put(gui->mlx, gui->win, 40, 50, 0x000000FF, "YOU WIN ;)");
	mlx_string_put(gui->mlx, gui->win, 40, 65, 0x000000FF, "PRESS R TO");
	mlx_string_put(gui->mlx, gui->win, 40, 80, 0x000000FF, "PLAY AGAIN");
	gui->end_game = 1;
	return (0);
}

/**
 * @brief Render the lost game screen.
 * @param gui The gui (graphical user interface) structure.
 * @return 0 to force the game to restart.
*/
int	ft_render_you_lost(t_gui *gui)
{
	mlx_string_put(gui->mlx, gui->win, 38, 50, 0xFF0000, "Oh no, Oh no, ");
	mlx_string_put(gui->mlx, gui->win, 38, 65, 0xFF0000, "Oh no no no");
	mlx_string_put(gui->mlx, gui->win, 38, 80, 0xFF0000, "YOU LOST :(");
	mlx_string_put(gui->mlx, gui->win, 38, 95, 0xFF0000, "PRESS R TO");
	mlx_string_put(gui->mlx, gui->win, 38, 110, 0xFF0000, "TRY AGAIN");
	gui->end_game = 1;
	return (0);
}

/**
 * @brief Function responsible for rendering the map of the game.
 * @param gui The gui (graphical user interface) structure.
 * @param i The index of the row.
 * @param j The index of the column.
 * @param s The size of the square.
 * @return void.
*/
void	ft_render_map(t_gui *gui, int i, int j, int s)
{
	while (gui->map->fill[i])
	{
		j = 0;
		while (gui->map->fill[i][j])
		{
			if (gui->map->fill[i][j] == gui->map->comp.wall)
				gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_WALL, &s, &s);
			else if (gui->map->fill[i][j] == gui->map->comp.empty)
				gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_FLOOR, &s, &s);
			else if (gui->map->fill[i][j] == gui->map->comp.obj.token)
				gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_OBJ, &s, &s);
			else if (gui->map->fill[i][j] == gui->map->comp.exit.token)
				gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_EXIT, &s, &s);
			else if (gui->map->fill[i][j] == gui->map->comp.player.token)
				gui->img = mlx_xpm_file_to_image(gui->mlx,
						gui->map->comp.player.sprite_path, &s, &s);
			else if (gui->map->fill[i][j] == gui->map->comp.enemy)
				gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_ENEMY, &s, &s);
			mlx_put_image_to_window(gui->mlx, gui->win, gui->img,
				j * gui->bpp, i * gui->bpp);
			mlx_destroy_image(gui->mlx, gui->img);
			j++;
		}
		i++;
	}
}

/**
 * @brief Function responsible for rendering the step counter on the screen.
 * @param gui The gui (graphical user interface) structure.
 * @return void.
*/
void	ft_render_step(t_gui *gui)
{
	char	*steps;
	char	*label;

	label = "STEP COUNTER: ";
	steps = ft_itoa(gui->map->comp.player.step_counter);
	mlx_string_put(gui->mlx, gui->win, 5, 20, 0x000000FF, label);
	mlx_string_put(gui->mlx, gui->win, 90, 20, 0x000000FF, steps);
	free(steps);
}
