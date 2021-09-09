/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_warnings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 14:52:13 by proberto          #+#    #+#             */
/*   Updated: 2021/09/09 03:13:27 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

/**
 * @brief Prints the error message.
 * @details The "\033[" is the escape sequence to change the color of the text,
 * the "31;" is the color code, the "1;" is the style, the "4" is the size 
 * of the style, the "m" is the end of the sequence, and the "0m" is the color 
 * code for the default.
*/
int	ft_error(char *message)
{
	printf("\033[31;1;4m" "Error\n     %s\n" "\033[0m", message);
	return (0);
}

int	ft_warning(char *message)
{
	printf("\033[33;1;4m" "Warning\n       %s\n" "\033[0m", message);
	return (0);
}
