/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 17:13:53 by proberto          #+#    #+#             */
/*   Updated: 2021/09/02 00:57:18 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	ft_free_map_config(t_map_config	*map_config)
{
	map_config->row = 0;
	map_config->col = 0;
	map_config->wall = '1';
	map_config->empty = '0';
	map_config->exit = 'E';
	map_config->object = 'C';
	map_config->player = 'P';
	map_config->enemy = 'X';
}

void	ft_free_map(char ***map)
{
	int	i;

	i = 0;
	while ((*map)[i])
		free((*map)[i++]);
	free(*map);
}
