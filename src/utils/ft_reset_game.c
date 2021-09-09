/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 03:35:06 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 03:35:12 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Reset the game.
 * @details Restart game and player step counter.
 * @param map The map to reset.
 * @param comp The components of the game to reset.
 * @return 0 to force the game to restart.
*/
int	ft_reset_game(t_map *map, t_components *comp)
{
	int	i;
	int	j;

	i = 1;
	while (i < (int)map->row - 1)
	{
		j = 1;
		while (j < (int)map->col - 1)
		{
			map->fill[i][j] = map->backup[i][j];
			j++;
		}
		i++;
	}
	comp->player.x = comp->player.init_x;
	comp->player.y = comp->player.init_y;
	comp->obj.qtd = comp->obj.init_qtd;
	comp->player.step_counter = 0;
	return (0);
}
