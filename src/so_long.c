/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:02:34 by proberto          #+#    #+#             */
/*   Updated: 2021/09/01 23:55:55 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	validate_args(int argc, char **argv);

/**
 * @brief Main function
 * @param argc Number of arguments
 * @param argv Argument array, where argv[0] is the program name and
 * argv [1] is expected the name of the map file
 * @return 0 if the program ends successfully, 1 otherwise
*/
int	main(int argc, char **argv)
{
	validate_args(argc, argv);
	if (!map_mngmt((const char **)argv))
		exit(1);
	return (0);
}

/**
 * @brief Validates the arguments passed to the program
 * @param argc Number of arguments
 * @param argv Argument array, where argv [1] is expected the name of the
 * map file
*/
static void	validate_args(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Error: No arguments provided\nusage: ./so_long <map>\n");
		exit(1);
	}
	else if (argc > 2)
		printf("Warning: too many arguments, only the first arg will be used\n");
	if (ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])) == NULL)
	{
		printf("Error: invalid file extension\nusage: ./so_long <map.ber>\n");
		exit(1);
	}
}
