/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 03:35:06 by proberto          #+#    #+#             */
/*   Updated: 2021/09/10 18:01:18 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Reset the game.
 * @details Restart the game map, the player's position, collectibles number, 
 * step counter and trigger render game.
 * @param gui The gui (graphical user interface) structure.
 * @return 0 to force the game to restart.
*/
int	ft_reset_game(t_gui *gui)
{
	int	i;
	int	j;

	i = 1;
	while (i < (int)gui->map->row - 1)
	{
		j = 1;
		while (j < (int)gui->map->col - 1)
		{
			gui->map->fill[i][j] = gui->map->backup[i][j];
			j++;
		}
		i++;
	}
	gui->map->comp.player.x = gui->map->comp.player.init_x;
	gui->map->comp.player.y = gui->map->comp.player.init_y;
	gui->map->comp.obj.qtd = gui->map->comp.obj.init_qtd;
	gui->map->comp.player.step_counter = 0;
	gui->end_game = 0;
	ft_render_game(gui);
	return (0);
}
