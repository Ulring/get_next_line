/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansoulim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 01:15:55 by ansoulim          #+#    #+#             */
/*   Updated: 2023/03/17 01:16:00 by ansoulim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	s1_len = 0;
	while (s1[s1_len] != '\0')
	{
		str[s1_len] = s1[s1_len];
		s1_len++;
	}
	s2_len = 0;
	while (s2[s2_len] != '\0')
	{
		str[s1_len] = s2[s2_len];
		s1_len++;
		s2_len++;
	}
	str[s1_len] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s);
	if (j <= start)
		len = 0;
	if (len > (j - start))
		len = (j - start);
	sub = malloc(sizeof(*sub) * (len + 1));
	if (!sub)
		return (NULL);
	while (len-- > 0)
	{
		sub[i] = *(s + start + i);
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

void	*ft_free_line_buffer(char **buffer_stash, int lines_to_create)
{
	char	*line;

	if (!*buffer_stash)
		return (NULL);
	if (lines_to_create == 0)
	{
		if (*buffer_stash)
		{
			free(*buffer_stash);
			*buffer_stash = NULL;
		}
		return (NULL);
	}
	else if (lines_to_create == 1)
	{
		line = ft_strdup(*buffer_stash);
		free(*buffer_stash);
		*buffer_stash = NULL;
		return (line);
	}
	return (NULL);
}
