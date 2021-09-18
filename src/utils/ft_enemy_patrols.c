/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemy_patrols.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:36:02 by proberto          #+#    #+#             */
/*   Updated: 2021/09/18 15:45:05 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Function responsible for rendering enemy movement.
 * @param gui Pointer to the gui (graphical user interface) struct.
 * @param i The index of the row.
 * @param j The index of the column.
 * @param s The size of the square.
 * @return void.
*/
static void	ft_render_move(t_gui *gui, int i, int j, int s)
{
	if (gui->end_game)
		return ;
	while (gui->map->fill[i])
	{
		j = 0;
		while (gui->map->fill[i][j])
		{
			if (gui->map->fill[i][j] == gui->map->comp.enemy)
				gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_ENEMY, &s, &s);
			else if (gui->map->fill[i][j] == gui->map->comp.empty)
				gui->img = mlx_xpm_file_to_image(gui->mlx, PATH_FLOOR, &s, &s);
			if (gui->map->fill[i][j] == gui->map->comp.enemy
				|| gui->map->fill[i][j] == gui->map->comp.empty)
			{
				mlx_put_image_to_window(gui->mlx, gui->win, gui->img,
					j * gui->bpp, i * gui->bpp);
				mlx_destroy_image(gui->mlx, gui->img);
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Function responsible for trying to move the enemy on the y axis of 
 * the map.
 * @details The function tries to move the enemy on the y axis of the map, to 
 * do this, it is first checked whether movement is possible on at least one of 
 * the sides (UP or DOWN), and then the functions to try to move enemies on 
 * the map are activated. A static variable is used to track the last side.
 * @param gui Pointer to the gui (graphical user interface) struct.
 * @param i Current row of the enemy.
 * @param j Current column of the enemy.
 * @return char 'x' which symbolizes the x axis, for the next enemy move.
*/
static char	ft_patrol_y(t_gui *gui, int i, int j)
{
	static char	side;
	static int	row;
	static int	count;

	if (gui->map->fill[i - 1][j] != gui->map->comp.empty
		&& gui->map->fill[i + 1][j] != gui->map->comp.empty)
		return ('x');
	if (!side || side == UP)
		side = ft_try_up(gui, i, j);
	if (side == DOWN)
	{
		side = ft_try_down(gui, i, j);
		if (side == UP && row != i)
			side = DOWN;
		row = i;
		count++;
		if (count == 1)
			return ('y');
		else
			count = 0;
	}
	return ('x');
}

/**
 * @brief Function responsible for trying to move the enemy on the x axis of 
 * the map.
 * @details The function tries to move the enemy on the x axis of the map, to 
 * do this, it is first checked whether movement is possible on at least one of 
 * the sides (Left or Right), and then the functions to try to move enemies on 
 * the map are activated. A static variable is used to track the last side.
 * @param gui Pointer to the gui (graphical user interface) struct.
 * @param i Current row of the enemy.
 * @param j Current column of the enemy.
 * @return char 'y' which symbolizes the y axis, for the next enemy move.
*/
static char	ft_patrol_x(t_gui *gui, int i, int *j)
{
	static char	side;

	if (gui->map->fill[i][*j - 1] != gui->map->comp.empty
		&& gui->map->fill[i][*j + 1] != gui->map->comp.empty)
		return ('y');
	if (!side || side == LEFT)
		side = ft_try_left(gui, i, *j);
	if (side == RIGHT)
		side = ft_try_right(gui, i, j);
	return ('y');
}

/**
 * @brief Function called by a loop (mlx_loop_hook) to move enemies on the map.
 * @details The function iterates through the map and checks for enemies. If it
 * exists, the function of trying to move the enemy is activated (axis x and y),
 * a static variable is used to track the last axis. Finally, the function to
 * render the motion on the map is called.
 * @param gui Pointer to the gui (graphical user interface) struct.
 * @return 0.
*/
int	ft_enemy_patrols(t_gui *gui)
{
	static char	axis;
	int			i;
	int			j;

	i = 0;
	while (gui->map->fill[i])
	{
		j = 0;
		while (gui->map->fill[i][j])
		{
			if (gui->map->fill[i][j] == gui->map->comp.enemy)
			{
				if (!axis || axis == 'y')
					axis = ft_patrol_y(gui, i, j);
				else
					axis = ft_patrol_x(gui, i, &j);
			}
			j++;
		}
		i++;
	}
	ft_render_move(gui, 0, 0, 0);
	return (0);
}
