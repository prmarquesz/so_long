/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 00:17:47 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 02:40:23 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	ft_validate_walled(t_map *map);
static int	ft_sub_validate_walled(t_map *map);
static int	ft_validate_core(t_map *map, int i, int j);
static int	ft_sub_validate_core(t_map *map, int i, int j);

/**
 * @brief Validates the map.
 * @details Checks if the map is valid (which means there are walls around 
 * it and the core has only known characters) and Check if the map has at least
 * one exit, one object and one player.
 * @param map The map to be validated.
 * @return 1 if the map is valid, 0 otherwise.
*/
int	ft_validate_map(t_map *map)
{
	if (!ft_validate_walled(map) || !ft_validate_core(map, 1, 1))
		return (0);
	if (!map->comp.player.qtd || !map->comp.exit.qtd || !map->comp.obj.qtd)
		return (ft_error("the map must have at least one exit ('E'), "
				"one collectible ('C'), and one starting position ('P')\n"));
	return (1);
}

/**
 * @brief Validates map enclosure.
 * @details Checks if the map contains empty rows and if the number of columns
 * is equal for all rows.
 * @param map The map to be validated.
 * @return 1 if the map is valid, 0 otherwise.
*/
static int	ft_validate_walled(t_map *map)
{
	int	i;

	i = 0;
	while (map->fill[i])
	{
		map->col = ft_strlen(map->fill[i]);
		if (!map->col)
			return (ft_error("there should be no empty lines in the "
					"map structure.\n"));
		if (i > 0 && i < (int)map->row)
		{
			if (map->col != ft_strlen(map->fill[i - 1]))
				return (ft_error("the number of columns"
						" must be the same for all rows.\n"));
		}
		i++;
	}
	return (ft_sub_validate_walled(map));
}

/**
 * @brief Validates map enclosure (sub function).
 * @details Check if the map is closed/surrounded by walls.
 * @return 1 if the map is valid, 0 otherwise.
*/
static int	ft_sub_validate_walled(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->fill[i])
	{
		j = 0;
		while (map->fill[i][j])
		{
			if (map->fill[i][j] != map->comp.wall)
				return (ft_error("the map must be closed/surrounded by walls "
						"(character '1')\n"));
			if (i > 0 && i < (int)map->row - 1)
				j += map->col - 1;
			else
				j++;
			if (j > (int)map->col)
				break ;
		}
		i++;
	}
	return (1);
}

/**
 * @brief Validates map core.
 * @details Check if the map has more than one starting position and one exit,
 * stores the position of the player, and the number of players, exits and
 * collectibles.
 * @param map The map to be validated.
 * @param i The row index.
 * @param j The column index.
 * @return 1 if the map is valid, 0 if there is more than one start position or 
 * more than one exit.
*/
static int	ft_validate_core(t_map *map, int i, int j)
{
	while (i < (int)map->row - 1)
	{
		j = 1;
		while (j < (int)map->col - 1)
		{
			if (!ft_sub_validate_core(map, i, j))
				return (0);
			if (map->comp.player.qtd > 1 || map->comp.exit.qtd > 1)
				return (ft_error("the map must have only one exit ('E') "
						"and one start position ('P')\n"));
			if (map->fill[i][j] == map->comp.player.token)
			{
				map->comp.player.qtd++;
				map->comp.player.x = j;
				map->comp.player.y = i;
			}
			if (map->fill[i][j] == map->comp.exit.token)
				map->comp.exit.qtd++;
			if (map->fill[i][j] == map->comp.obj.token)
				map->comp.obj.qtd++;
			j++;
		}
		i++;
	}
	return (1);
}

/**
 * @brief Validates map core (sub function).
 * @details Check if the map is composed only key characters.
 * @return 1 if the map is valid, 0 otherwise.
*/
static int	ft_sub_validate_core(t_map *map, int i, int j)
{
	if (map->fill[i][j] != map->comp.wall &&
		map->fill[i][j] != map->comp.empty &&
		map->fill[i][j] != map->comp.enemy &&
		map->fill[i][j] != map->comp.player.token &&
		map->fill[i][j] != map->comp.exit.token &&
		map->fill[i][j] != map->comp.obj.token)
		return (ft_error("unknown key char\n"));
	map->comp.player.init_x = map->comp.player.x;
	map->comp.player.init_y = map->comp.player.y;
	map->comp.obj.init_qtd = map->comp.obj.qtd;
	return (1);
}
