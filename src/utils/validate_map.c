/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 00:17:47 by proberto          #+#    #+#             */
/*   Updated: 2021/09/02 01:46:12 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	ft_sub_validate_walled(char ***map, t_map_config *map_config);
static int	ft_sub_validate_core(char ***map, t_map_config *map_config);

/**
 * @brief Validates map enclosure.
 * @details Checks if the map contains empty rows and if the number of columns
 * is equal for all rows.
 * @param map The map to be validated.
 * @param map_config The map configuration.
 * @return 1 if the map is valid, 0 otherwise.
*/
int	ft_validate_walled(char ***map, t_map_config *map_config)
{
	int	i;

	i = 0;
	while ((*map)[i])
	{
		map_config->col = ft_strlen((*map)[i]);
		if (!map_config->col)
			return (ft_error("Error\n there should be no empty lines in the "
					"map structure."));
		if (i > 0 && i < (int)map_config->row)
		{
			if (map_config->col != ft_strlen((*map)[i - 1]))
				return (ft_error("Error\n the number of columns"
						" must be the same for all rows."));
		}
		i++;
	}
	if (!ft_sub_validate_walled(map, map_config))
		return (0);
	return (1);
}

/**
 * @brief Validates map enclosure (sub function).
 * @details Check if the map is closed/surrounded by walls.
 * @return 1 if the map is valid, 0 otherwise.
*/
static int	ft_sub_validate_walled(char ***map, t_map_config *map_config)
{
	int	i;
	int	j;

	i = 0;
	while ((*map)[i])
	{
		j = 0;
		while ((*map)[i][j])
		{
			if ((*map)[i][j] != map_config->wall)
				return (ft_error("Error\n "
						"the map must be closed/surrounded by walls "
						"(character '1')"));
			if (i > 0 && i < (int)map_config->row - 1)
				j += map_config->col - 1;
			else
				j++;
			if (j > (int)map_config->col)
				break ;
		}
		i++;
	}
	return (1);
}

/**
 * @brief Validates map core.
 * @details Check if the map is composed only key characters.
 * @param map The map to be validated.
 * @param map_config The map configuration.
 * @return 1 if the map is valid, 0 otherwise.
*/
int	ft_validate_core(char ***map, t_map_config *map_config)
{
	int	i;
	int	j;

	i = 1;
	while (i < (int)map_config->row - 1)
	{
		j = 1;
		while (j < (int)map_config->col - 1)
		{
			if ((*map)[i][j] != map_config->empty &&
				(*map)[i][j] != map_config->exit &&
				(*map)[i][j] != map_config->object &&
				(*map)[i][j] != map_config->player &&
				(*map)[i][j] != map_config->enemy &&
				(*map)[i][j] != map_config->wall)
				return (ft_error("Error\n unknown key char"));
			j++;
		}
		i++;
	}
	if (!ft_sub_validate_core(map, map_config))
		return (0);
	return (1);
}

/**
 * @brief Validates map core (sub function).
 * @details Check if the map has at least one exit, one object and one player.
 * @return 1 if the map is valid, 0 otherwise.
*/
static int	ft_sub_validate_core(char ***map, t_map_config *map_config)
{
	int	i;
	int	exit_count;
	int	object_count;
	int	player_count;

	i = 1;
	exit_count = 0;
	object_count = 0;
	player_count = 0;
	while (i < (int)map_config->row - 1)
	{
		if (ft_memchr((*map)[i], map_config->exit, map_config->col))
			exit_count++;
		if (ft_memchr((*map)[i], map_config->object, map_config->col))
			object_count++;
		if (ft_memchr((*map)[i], map_config->player, map_config->col))
			player_count++;
		i++;
	}
	if (!exit_count || !object_count || !player_count)
		return (ft_error("Error\n map must have at least one exit ('E'), "
				"one collectible ('C'), and one starting position ('P')"));
	return (1);
}
