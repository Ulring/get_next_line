/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 01:15:38 by ansoulim          #+#    #+#             */
/*   Updated: 2023/03/17 01:15:40 by ansoulim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_copy_to_line_buffer(char *buffer_stash, char *buffer)
{
	char	*temp;
	char	*res;

	res = NULL;
	if (!buffer_stash && buffer)
	{
		res = ft_strdup(buffer);
		if (!res)
			return (ft_free_line_buffer(&res, 0));
		return (res);
	}
	temp = ft_strdup(buffer_stash);
	if (!temp)
	{
		ft_free_line_buffer(&buffer_stash, 0);
		return (ft_free_line_buffer(&temp, 0));
	}
	ft_free_line_buffer(&buffer_stash, 0);
	res = ft_strjoin(temp, buffer);
	if (!res)
		ft_free_line_buffer(&res, 0);
	ft_free_line_buffer(&temp, 0);
	return (res);
}

static int	ft_has_newline(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_extract_line(char *buffer_stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!buffer_stash)
		return (ft_free_line_buffer(&buffer_stash, 0));
	while (buffer_stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (ft_free_line_buffer(&line, 0));
	j = 0;
	while (j < i + 1)
	{
		line[j] = buffer_stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_recreate_line_buffer(char *buffer_stash)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!buffer_stash)
		return (NULL);
	while (buffer_stash[i] != '\n')
		i++;
	if (buffer_stash[i + 1] == '\0')
		return (ft_free_line_buffer(&buffer_stash, 0));
	res = ft_substr(buffer_stash, i + 1, ft_strlen(buffer_stash));
	if (!res)
	{
		ft_free_line_buffer(&buffer_stash, 0);
		return (NULL);
	}
	ft_free_line_buffer(&buffer_stash, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		bytes_read;
	static char	*buffer_stash = NULL;
	char		*line;

	line = NULL;
	bytes_read = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((bytes_read <= 0 && !buffer_stash) || bytes_read == -1)
			return (ft_free_line_buffer(&buffer_stash, 0));
		buffer[bytes_read] = '\0';
		buffer_stash = ft_copy_to_line_buffer(buffer_stash, buffer);
		if (ft_has_newline(buffer_stash))
		{
			line = ft_extract_line(buffer_stash);
			if (!line)
				return (ft_free_line_buffer(&buffer_stash, 0));
			return (buffer_stash = ft_recreate_line_buffer(buffer_stash), line);
		}
	}
	return (ft_free_line_buffer(&buffer_stash, 1));
}
