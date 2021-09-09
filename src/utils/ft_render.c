/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:13:19 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 03:21:53 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Function responsible for rendering the map of the game.
 * @param gui The gui (graphical user interface) structure.
 * @param i The index of the row.
 * @param j The index of the column.
 * @param s The size of the square.
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
				gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_PLAYER, &s, &s);
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
 * @brief Function responsible for rendering the step counter.
 * @param gui The gui (graphical user interface) structure.
*/
void	ft_render_step(t_gui *gui)
{
	char	*steps;
	char	*label;

	label = "STEP COUNTER: ";
	steps = ft_itoa(gui->map->comp.player.step_counter);
	mlx_string_put(gui->mlx, gui->win, 20, 20, 0x000000FF, label);
	mlx_string_put(gui->mlx, gui->win, 120, 20, 0x000000FF, steps);
	free(steps);
}
