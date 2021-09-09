/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_mngmt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:09:59 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 03:31:41 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	ft_config_map(t_map *map, const char *argv);
static int	ft_number_of_lines(const char *argv, int i, int ret);
static int	ft_get_map(char **map, const char *argv, int i, int ret);

/**
 * @brief Management of the map.
 * @details This function is responsible for get the map, send it to the 
 * validation and render functions.
 * @param argv The name of the file to read.
 * @return 1 if all is successful, 0 otherwise.
*/
int	ft_map_mngmt(const char **argv)
{
	int		ret;
	t_map	map;

	if (!ft_config_map(&map, argv[1]))
		return (0);
	if (!ft_get_map(map.fill, argv[1], 0, 1)
		|| !ft_get_map(map.backup, argv[1], 0, 1))
		return (0);
	ret = ft_validate_map(&map);
	if (ret)
		ret = ft_build_game(&map);
	ft_free_map(map.fill);
	ft_free_map(map.backup);
	return (ret);
}

/**
 * @brief Initial map setup.
 * @param map The map to configure.
 * @param argv The name of the file to read.
 * @return 1 if the map was successfully created, 0 otherwise.
*/
static int	ft_config_map(t_map *map, const char *argv)
{
	map->comp.wall = '1';
	map->comp.empty = '0';
	map->comp.enemy = 'X';
	map->comp.player.token = 'P';
	map->comp.exit.token = 'E';
	map->comp.obj.token = 'C';
	map->comp.player.qtd = 0;
	map->comp.exit.qtd = 0;
	map->comp.obj.qtd = 0;
	map->comp.player.step_counter = 0;
	map->col = 0;
	map->row = (size_t)ft_number_of_lines(argv, 0, 1);
	if (!map->row)
		return (0);
	map->fill = (char **)malloc(sizeof(char *) * (map->row + 1));
	map->backup = (char **)malloc(sizeof(char *) * (map->row + 1));
	if (!map->fill || !map->backup)
		return (ft_error("failed trying to allocate map\n"));
	map->fill[map->row] = NULL;
	map->backup[map->row] = NULL;
	return (1);
}

/**
 * @brief Counts the number of lines in the file.
 * @param argv The name of the file to read.
 * @param i Auxiliary variable.
 * @param ret Auxiliary variable.
 * @return The number of lines if success, 0 otherwise.
*/
static int	ft_number_of_lines(const char *argv, int i, int ret)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (ft_error("file not found\n"));
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		free(line);
		if (ret == -1)
			return (ft_error("failed trying to read file\n"));
		i++;
	}
	close(fd);
	return (i);
}

/**
 * @brief Copies the map from the file to the array map->fill.
 * @param map The map to fill.
 * @param argv The name of the file to read.
 * @param i Auxiliary variable.
 * @param ret Auxiliary variable.
 * @return The number of lines if success, 0 otherwise.
*/
static int	ft_get_map(char **map, const char *argv, int i, int ret)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (ft_error("file not found\n"));
	while (ret > 0)
	{
		ret = get_next_line(fd, &map[i++]);
		if (ret == -1)
			return (ft_error("failed trying to read file\n"));
	}
	close(fd);
	return (i);
}
