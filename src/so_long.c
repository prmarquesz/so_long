/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:02:34 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 02:13:56 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	ft_validate_args(int argc, char **argv);

/**
 * @brief Main function.
 * @param argc Number of arguments.
 * @param argv Argument array, where argv[0] is the program name and
 * argv [1] is expected the name of the map file.
 * @return 0 if the program ends successfully, 1 otherwise.
*/
int	main(int argc, char **argv)
{
	ft_validate_args(argc, argv);
	if (!ft_map_mngmt((const char **)argv))
		exit(1);
	return (0);
}

/**
 * @brief Validates the arguments passed to the program.
 * @param argc Number of arguments.
 * @param argv Argument array, where argv [1] is expected the name of the
 * map file.
*/
static void	ft_validate_args(int argc, char **argv)
{
	char	*file;
	char	*extention;
	size_t	len_file;
	size_t	len_ext;

	file = argv[1];
	extention = ".ber";
	len_ext = ft_strlen(extention);
	len_file = ft_strlen(file) - ft_strlen(extention);
	if (argc < 2)
	{
		ft_error("no arguments provided\n"
			"	 usage: ./so_long <map>\n");
		exit(1);
	}
	else if (argc > 2)
		ft_warning("too many arguments, only the first arg will be used\n");
	if (ft_strnstr(file + len_file, extention, len_ext) == NULL)
	{
		ft_error("invalid file extension\n"
			"	 usage: ./so_long <map.ber>\n");
		exit(1);
	}
}
