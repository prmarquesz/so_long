/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:13:19 by proberto          #+#    #+#             */
/*   Updated: 2021/09/02 01:00:08 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Render the game map on the screen
 * @param map The map to render
 * @return 1 if the map was rendered, 0 otherwise
*/
int	ft_render_map(char ***map)
{
	int	i;

	i = 0;
	while ((*map)[i])
	{
		printf("%s\n", (*map)[i]);
		i++;
	}
	return (1);
}
