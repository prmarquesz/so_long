/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: proberto <proberto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:12:06 by proberto          #+#    #+#             */
/*   Updated: 2021/08/27 21:43:06 by proberto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_stoline(char **line, char **storage, ssize_t offset);
ssize_t	ft_get_buffer(int fd, char **line, char **buffer, char **storage);
ssize_t	ft_get_line(char **line, char **buffer, char **storage);
ssize_t	ft_get_line_break(ssize_t i, char **line, char **buffer,
			char **storage);

int	get_next_line(int fd, char **line)
{
	static char	*storage;
	char		*buffer;
	ssize_t		res;

	if (fd < 0 || BUFFER_SIZE <= 0 || line == 0)
		return (-1);
	res = ft_is_there_a_line_break(storage);
	if (res >= 0)
	{
		res = ft_stoline(line, &storage, res);
		if (res == -1)
			*line = NULL;
		return (res);
	}
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
	{
		*line = NULL;
		return (-1);
	}
	res = ft_get_buffer(fd, line, &buffer, &storage);
	if (res < 0)
		*line = NULL;
	free(buffer);
	return (res);
}

ssize_t	ft_stoline(char **line, char **storage, ssize_t offset)
{
	size_t	len;

	*line = (char *)ft_calloc(offset + 1, sizeof(char));
	if (!*line)
		return (-1);
	ft_memcpy(*line, *storage, offset);
	len = ft_strlen((char *)*storage + offset + 1);
	ft_memcpy(*storage, (char *)*storage + offset + 1, len);
	*(*storage + len) = (unsigned char)0;
	*storage = (char *)ft_realloc(*storage, len + 1);
	if (*storage)
		return (1);
	else
		free(*line);
	return (-1);
}

ssize_t	ft_get_buffer(int fd, char **line, char **buffer, char **storage)
{
	ssize_t	offset;
	size_t	len;
	int		res;

	len = ft_strlen(*buffer);
	res = read(fd, (char *)*buffer + len, BUFFER_SIZE);
	if (res > 0)
	{
		offset = ft_is_there_a_line_break(*buffer);
		if (offset == -1)
		{
			len = ft_strlen(*buffer);
			*buffer = (char *)ft_realloc(*buffer, len + BUFFER_SIZE + 1);
			if (!*buffer)
				return (-1);
			return (ft_get_buffer(fd, line, buffer, storage));
		}
		return (ft_get_line_break(offset, line, buffer, storage));
	}
	else if (res == 0 && (*buffer || *storage))
		return (ft_get_line(line, buffer, storage));
	else
		return (-1);
}

ssize_t	ft_get_line(char **line, char **buffer, char **storage)
{
	size_t	len_buffer;
	size_t	len_sotrage;

	len_buffer = ft_strlen(*buffer);
	len_sotrage = ft_strlen(*storage);
	*line = (char *)ft_calloc((len_buffer + len_sotrage + 1), sizeof(char));
	if (!*line)
		return (-1);
	if (*storage)
	{
		ft_memcpy(*line, *storage, len_sotrage);
		ft_memcpy((char *)*line + len_sotrage, *buffer, len_buffer);
		free(*storage);
		*storage = NULL;
	}
	else
		ft_memcpy(*line, *buffer, len_buffer);
	return (0);
}

ssize_t	ft_get_line_break(ssize_t i, char **line, char **buffer, char **storage)
{
	size_t	len_buffer;
	size_t	len_sotrage;

	len_buffer = ft_strlen(*buffer);
	len_sotrage = ft_strlen(*storage);
	*line = (char *)ft_calloc((i + len_sotrage + 1), sizeof(char));
	if (!*line)
		return (-1);
	ft_memcpy(*line, *storage, len_sotrage);
	ft_memcpy((char *)*line + len_sotrage, *buffer, i);
	free(*storage);
	*storage = NULL;
	if (*buffer + i + 1)
	{
		*storage = (char *)ft_calloc((len_buffer - i), sizeof(char));
		if (!*storage)
		{
			free(*line);
			return (-1);
		}
		ft_memcpy(*storage, (char *)*buffer + i + 1, len_buffer - i - 1);
	}
	return (1);
}
