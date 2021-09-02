/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mngmt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:09:59 by proberto          #+#    #+#             */
/*   Updated: 2021/09/02 01:28:09 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	ft_count_or_write(char ***map, const char *argv, int opt);
static int	ft_sub_count(int fd, char ***map);
static int	ft_sub_write(int fd, char ***map);

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

/**
 * @brief Controls the options to count the number of lines and 
 * write the map in the array
 * @param map The map to be filled
 * @param argv The name of the file to read
 * @param opt The option to be used
 * @return The number of lines in the file
*/
static int	ft_count_or_write(char ***map, const char *argv, int opt)
{
	int	fd;
	int	ret;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (ft_error("Error\n file not found"));
	if (opt == COUNT)
		ret = ft_sub_count(fd, map);
	else if (opt == WRITE)
		ret = ft_sub_write(fd, map);
	close(fd);
	return (ret);
}

/**
 * @brief Counts the number of lines in the file
 * @param fd The file descriptor
 * @param map The line to be filled
 * @return The number of lines in the file
*/
static int	ft_sub_count(int fd, char ***map)
{
	int	ret;
	int	i;

	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &(*map)[0]);
		free((*map)[0]);
		if (ret == -1)
			return (ft_error("Error\n failed trying to read file"));
		i++;
	}
	return (i);
}

/**
 * @brief Writes the map contained in the file to the map array
 * @param fd The file descriptor
 * @param map The map to be filled
 * @return The number of lines in the file
*/
static int	ft_sub_write(int fd, char ***map)
{
	int	ret;
	int	i;

	ret = 1;
	i = 0;
	while (ret > 0)
	{
		ret = get_next_line(fd, &(*map)[i++]);
		if (ret == -1)
			return (ft_error("Error\n failed trying to read file"));
	}
	return (i);
}
