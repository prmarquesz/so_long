/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 03:34:48 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 03:34:51 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Move the player in the direction of the arrow key.
 * @param map The map of the game.
 * @param comp The components of the map.
 * @param x The x position of the player.
 * @param y The y position of the player.
 * @return 1 if the player has moved, 0 otherwise.
*/
static int	ft_move(t_map *map, t_components *comp, int x, int y)
{
	if (map->fill[y][x] == comp->enemy)
		return (ft_reset_game(map, comp));
	if (map->fill[y][x] == comp->exit.token)
	{
		if (comp->obj.qtd)
			return (0);
		//you_win();
	}
	if (map->fill[y][x] == comp->empty)
	{
		map->fill[y][x] = comp->player.token;
		comp->player.x = x;
		comp->player.y = y;
		comp->player.step_counter++;
	}
	if (map->fill[y][x] == comp->obj.token)
	{
		map->fill[y][x] = comp->player.token;
		comp->obj.qtd--;
		comp->player.x = x;
		comp->player.y = y;
		comp->player.step_counter++;
	}
	return (1);
}

/**
 * @brief Move the player in the x axis.
 * @param gui The gui (graphical user interface) struct.
 * @param side The side to move (RIGHT or LEFT).
*/
void	ft_move_x(t_gui *gui, t_sides side)
{
	int	x;
	int	y;

	x = gui->map->comp.player.x;
	y = gui->map->comp.player.y;
	if (side == RIGHT)
	{
		x++;
		if (gui->map->fill[y][x] == gui->map->comp.wall)
			return ;
		if (!ft_move(gui->map, &(gui->map->comp), x, y))
			return ;
		gui->map->fill[y][x - 1] = gui->map->comp.empty;
	}
	else
	{
		x--;
		if (gui->map->fill[y][x] == gui->map->comp.wall)
			return ;
		if (!ft_move(gui->map, &(gui->map->comp), x, y))
			return ;
		gui->map->fill[y][x + 1] = gui->map->comp.empty;
	}
}

/**
 * @brief Move the player in the y axis.
 * @param gui The gui (graphical user interface) struct.
 * @param side The side to move (UP or DOWN).
*/
void	ft_move_y(t_gui *gui, t_sides side)
{
	int	x;
	int	y;

	x = gui->map->comp.player.x;
	y = gui->map->comp.player.y;
	if (side == UP)
	{
		y--;
		if (gui->map->fill[y][x] == gui->map->comp.wall)
			return ;
		if (!ft_move(gui->map, &(gui->map->comp), x, y))
			return ;
		gui->map->fill[y + 1][x] = gui->map->comp.empty;
	}
	else
	{
		y++;
		if (gui->map->fill[y][x] == gui->map->comp.wall)
			return ;
		if (!ft_move(gui->map, &(gui->map->comp), x, y))
			return ;
		gui->map->fill[y - 1][x] = gui->map->comp.empty;
	}
}
