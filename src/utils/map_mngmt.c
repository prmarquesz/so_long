/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mngmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:09:59 by proberto          #+#    #+#             */
/*   Updated: 2021/09/02 01:22:28 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Management of the map
 * @param argv The name of the file to read
 * @return 1 if the map was successfully created, 0 otherwise
*/
int	map_mngmt(const char **argv)
{
	char			**map;
	int				ret;
	t_map_config	map_config;

	ft_free_map_config(&map_config);
	map_config.row = (size_t)ft_count_or_write(&map, argv[1], COUNT);
	if (!map_config.row)
		return (0);
	map = (char **)malloc(sizeof(char *) * (map_config.row + 1));
	if (!map)
		return (ft_error("Error\n failed trying to allocate map"));
	map[map_config.row] = NULL;
	ft_count_or_write(&map, argv[1], WRITE);
	ret = ft_validate_walled(&map, &map_config);
	ret = ft_validate_core(&map, &map_config);
	ret = ft_render_map(&map);
	ft_free_map(&map);
	return (ret);
}
