/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 03:34:48 by proberto          #+#    #+#             */
/*   Updated: 2021/09/10 17:39:56 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Assign the xpm files path to the main variable.
 * @details Assigns the xpm file path containing the sprite where the character 
 * is standing (varying according to which side the move was ended) 
 * to the variable that will be read in the map rendering.
 * @param gui The gui (graphical user interface) structure.
 * @param side The side of the character where the move ended.
 * @return void.
*/
void	stop_player(t_gui *gui, char side)
{
	if (side == UP)
		gui->map->comp.player.sprite_path = PATH_PLAYER_UP;
	else if (side == DOWN)
		gui->map->comp.player.sprite_path = PATH_PLAYER_DOWN;
	else if (side == RIGHT)
		gui->map->comp.player.sprite_path = PATH_PLAYER_RIGHT;
	else if (side == LEFT)
		gui->map->comp.player.sprite_path = PATH_PLAYER_LEFT;
	if (side == UP || side == DOWN || side == RIGHT || side == LEFT)
		ft_render_game(gui);
}

/**
 * @brief Assign the xpm files path to the main variable.
 * @details Alternately assign the path of the xpm file containing the sprite 
 * the character is about to move (varying according to which side the move 
 * will occur) to the variable that will be read in the map rendering.
 * @param gui The gui (graphical user interface) structure.
 * @param side The side of the character where the move will occur.
 * @return void.
*/
static void	update_player_direction(t_gui *gui, char side)
{
	static int	movement;

	if (movement++ == 0)
	{
		if (side == UP)
			gui->map->comp.player.sprite_path = PATH_PLAYER_UP1;
		if (side == DOWN)
			gui->map->comp.player.sprite_path = PATH_PLAYER_DOWN1;
		if (side == RIGHT)
			gui->map->comp.player.sprite_path = PATH_PLAYER_RIGHT1;
		if (side == LEFT)
			gui->map->comp.player.sprite_path = PATH_PLAYER_LEFT1;
		ft_render_game(gui);
		return ;
	}
	if (side == UP)
		gui->map->comp.player.sprite_path = PATH_PLAYER_UP2;
	if (side == DOWN)
		gui->map->comp.player.sprite_path = PATH_PLAYER_DOWN2;
	if (side == RIGHT)
		gui->map->comp.player.sprite_path = PATH_PLAYER_RIGHT2;
	if (side == LEFT)
		gui->map->comp.player.sprite_path = PATH_PLAYER_LEFT2;
	movement = 0;
	ft_render_game(gui);
}

/**
 * @brief Move the player in the desired direction.
 * @details Move the player in the desired direction;
 * 		if it is equal to the enemy, the player will lose the game;
 * 		if it is equal to exit and all collectibles have been collected, 
 * the player will win the game;
 * 		if it equals empty, the player will move normally, his position will be 
 * updated, and de step counter will be incremented.
 * @param gui The gui (graphical user interface) struct.
 * @param x The position on map where the player is about to move (x axis).
 * @param y The position on map where the player is about to move (y axis).
 * @return 1 if the player has moved, 0 otherwise.
*/
static int	ft_move(t_gui *gui, int x, int y)
{
	if (gui->map->fill[y][x] == gui->map->comp.enemy)
		return (ft_render_you_lost(gui));
	if (gui->map->fill[y][x] == gui->map->comp.exit.token)
	{
		if (gui->map->comp.obj.qtd)
			return (0);
		return (ft_render_you_win(gui, x, y));
	}
	if (gui->map->fill[y][x] == gui->map->comp.empty)
	{
		gui->map->fill[y][x] = gui->map->comp.player.token;
		gui->map->comp.player.x = x;
		gui->map->comp.player.y = y;
		gui->map->comp.player.step_counter++;
	}
	if (gui->map->fill[y][x] == gui->map->comp.obj.token)
	{
		gui->map->fill[y][x] = gui->map->comp.player.token;
		gui->map->comp.obj.qtd--;
		gui->map->comp.player.x = x;
		gui->map->comp.player.y = y;
		gui->map->comp.player.step_counter++;
	}
	return (1);
}

/**
 * @brief Move the player in the x axis.
 * @details Recovers the player's position on the map. Triggers player sprite 
 * update and player move (if the next position is different from a wall), 
 * if the move occurs, an empty space is assigned to the position the player 
 * was in before the move. 
 * @param gui The gui (graphical user interface) struct.
 * @param side The side to move (RIGHT or LEFT).
 * @return 1 if the player has moved, 0 otherwise.
*/
int	ft_move_x(t_gui *gui, char side)
{
	int	x;
	int	y;

	x = gui->map->comp.player.x;
	y = gui->map->comp.player.y;
	update_player_direction(gui, side);
	if (side == RIGHT)
	{
		x++;
		if (gui->map->fill[y][x] == gui->map->comp.wall)
			return (0);
		if (!ft_move(gui, x, y))
			return (0);
		gui->map->fill[y][x - 1] = gui->map->comp.empty;
	}
	else
	{
		x--;
		if (gui->map->fill[y][x] == gui->map->comp.wall)
			return (0);
		if (!ft_move(gui, x, y))
			return (0);
		gui->map->fill[y][x + 1] = gui->map->comp.empty;
	}
	return (1);
}

/**
 * @brief Move the player in the y axis.
 * @details Recovers the player's position on the map. Triggers player sprite 
 * update and player move (if the next position is different from a wall), 
 * if the move occurs, an empty space is assigned to the position the player 
 * was in before the move.
 * @param gui The gui (graphical user interface) struct.
 * @param side The side to move (UP or DOWN).
 * @return 1 if the player has moved, 0 otherwise.
*/
int	ft_move_y(t_gui *gui, char side)
{
	int	x;
	int	y;

	x = gui->map->comp.player.x;
	y = gui->map->comp.player.y;
	update_player_direction(gui, side);
	if (side == UP)
	{
		y--;
		if (gui->map->fill[y][x] == gui->map->comp.wall)
			return (0);
		if (!ft_move(gui, x, y))
			return (0);
		gui->map->fill[y + 1][x] = gui->map->comp.empty;
	}
	else
	{
		y++;
		if (gui->map->fill[y][x] == gui->map->comp.wall)
			return (0);
		if (!ft_move(gui, x, y))
			return (0);
		gui->map->fill[y - 1][x] = gui->map->comp.empty;
	}
	return (1);
}
