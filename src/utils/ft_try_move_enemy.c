/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_try_move_enemy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:36:19 by proberto          #+#    #+#             */
/*   Updated: 2021/09/18 16:08:36 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Try to move the enemy up.
 * @details If the top row and column are enemies, or an exit, or a collectible,
 * or a wall, return in the reverse direction (DOWN). If the top row and column 
 * is empty space, move the enemy up. And if is a player, kill him and game over.
 * @param gui Pointer to the gui (graphical user interface) struct.
 * @param i The index of the row.
 * @param j The index of the column.
 * @return The new direction of the enemy (UP or DOWN). 
*/
char	ft_try_up(t_gui *gui, int i, int j)
{
	if (gui->map->fill[i - 1][j] == gui->map->comp.enemy
		|| gui->map->fill[i - 1][j] == gui->map->comp.exit.token
		|| gui->map->fill[i - 1][j] == gui->map->comp.obj.token
		|| gui->map->fill[i - 1][j] == gui->map->comp.wall)
		return (DOWN);
	else if (gui->map->fill[i - 1][j] == gui->map->comp.empty)
	{
		gui->map->fill[i - 1][j] = gui->map->comp.enemy;
		gui->map->fill[i][j] = gui->map->comp.empty;
	}
	else
		ft_render_you_lost(gui);
	return (UP);
}

/**
 * @brief Try to move the enemy down.
 * @details If the bottom row and column are enemies, or an exit, or a 
 * collectible, or a wall, return in the reverse direction (UP). If the bottom 
 * row and column is empty space, move the enemy down. And if is a player, kill 
 * him and game over.
 * @param gui Pointer to the gui (graphical user interface) struct.
 * @param i The index of the row.
 * @param j The index of the column.
 * @return The new direction of the enemy (UP or DOWN). 
*/
char	ft_try_down(t_gui *gui, int i, int j)
{
	static int	count;
	static int	row;
	static int	col;

	if (gui->map->fill[i + 1][j] == gui->map->comp.enemy
		|| gui->map->fill[i + 1][j] == gui->map->comp.exit.token
		|| gui->map->fill[i + 1][j] == gui->map->comp.obj.token
		|| gui->map->fill[i + 1][j] == gui->map->comp.wall)
		return (UP);
	else if (gui->map->fill[i + 1][j] == gui->map->comp.empty)
	{
		if (row == i && col < j)
			count = count;
		else
			count++;
		row = i;
		col = j;
		if (count % 2 == 1)
			return (DOWN);
		gui->map->fill[i + 1][j] = gui->map->comp.enemy;
		gui->map->fill[i][j] = gui->map->comp.empty;
	}
	else
		ft_render_you_lost(gui);
	return (DOWN);
}

/**
 * @brief Try to move the enemy to the left.
 * @details If the left column are enemies, or an exit, or a collectible, or 
 * a wall, return in the reverse direction (RIGHT). If the left column is empty 
 * space, move the enemy to the left. And if is a player, kill him and game over.
 * @param gui Pointer to the gui (graphical user interface) struct.
 * @param i The index of the row.
 * @param j The index of the column.
 * @return The new direction of the enemy (LEFT or RIGHT). 
*/
char	ft_try_left(t_gui *gui, int i, int j)
{
	if (gui->map->fill[i][j - 1] == gui->map->comp.enemy
		|| gui->map->fill[i][j - 1] == gui->map->comp.exit.token
		|| gui->map->fill[i][j - 1] == gui->map->comp.obj.token
		|| gui->map->fill[i][j - 1] == gui->map->comp.wall)
		return (RIGHT);
	else if (gui->map->fill[i][j - 1] == gui->map->comp.empty)
	{
		gui->map->fill[i][j - 1] = gui->map->comp.enemy;
		gui->map->fill[i][j] = gui->map->comp.empty;
	}
	else
		ft_render_you_lost(gui);
	return (LEFT);
}

/**
 * @brief Try to move the enemy to the right.
 * @details If the right column are enemies, or an exit, or a collectible, or 
 * a wall, return in the reverse direction (LEFT). If the right column is empty 
 * space, move the enemy to the right. And if is a player, kill him and game 
 * over.
 * @param gui Pointer to the gui (graphical user interface) struct.
 * @param i The index of the row.
 * @param j The index of the column.
 * @return The new direction of the enemy (LEFT or RIGHT). 
*/
char	ft_try_right(t_gui *gui, int i, int *j)
{
	if (gui->map->fill[i][*j + 1] == gui->map->comp.enemy
		|| gui->map->fill[i][*j + 1] == gui->map->comp.exit.token
		|| gui->map->fill[i][*j + 1] == gui->map->comp.obj.token
		|| gui->map->fill[i][*j + 1] == gui->map->comp.wall)
		return (LEFT);
	else if (gui->map->fill[i][*j + 1] == gui->map->comp.empty)
	{
		gui->map->fill[i][*j + 1] = gui->map->comp.enemy;
		gui->map->fill[i][*j] = gui->map->comp.empty;
		*j += 1;
	}
	else
		ft_render_you_lost(gui);
	return (RIGHT);
}
