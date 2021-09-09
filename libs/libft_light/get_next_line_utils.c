/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 14:17:22 by proberto          #+#    #+#             */
/*   Updated: 2021/08/27 21:56:47 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_is_there_a_line_break(char *str)
{
	ssize_t	offset;

	if (!str)
		return (-1);
	offset = 0;
	while (*(str + offset))
	{
		if (str[offset] == '\n')
			return (offset);
		offset++;
	}
	return (-1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_src;
	unsigned char	*ptr_dst;

	if (!dst && !src)
		return (dst);
	i = 0;
	ptr_src = (unsigned char *) src;
	ptr_dst = (unsigned char *) dst;
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	len = count * size;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = (unsigned char) 0;
		i++;
	}
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (!ptr)
		return (NULL);
	new_ptr = ft_calloc(size, sizeof(char));
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (ft_memcpy(new_ptr, ptr, ft_strlen(ptr)))
	{
		free(ptr);
		return (new_ptr);
	}	
	else
	{
		free(new_ptr);
		free(ptr);
		return (NULL);
	}
}
