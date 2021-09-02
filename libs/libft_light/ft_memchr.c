/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:55:28 by proberto          #+#    #+#             */
/*   Updated: 2021/09/01 19:28:21 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_aux;
	unsigned char	*end_s;

	s_aux = (unsigned char *) s;
	end_s = (unsigned char *) s + n;
	while (s_aux < end_s)
	{
		if (*s_aux == (unsigned char) c)
			return (s_aux);
		s_aux++;
	}
	return (NULL);
}
