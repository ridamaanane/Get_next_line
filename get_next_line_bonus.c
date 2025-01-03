/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:23:23 by rmaanane          #+#    #+#             */
/*   Updated: 2025/01/02 19:16:06 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char *cache)
{
	char	*line;
	char	*line_pos;

	if (!cache || !*cache)
		return (NULL);
	line_pos = ft_strchr(cache, '\n');
	if (line_pos)
		line = ft_substr(cache, 0, (line_pos - cache + 1));
	else
		line = ft_strdup(cache);
	return (line);
}

char	*update_cache(char *cache)
{
	char	*line_pos;
	char	*new_cache;

	if (!cache || !*cache)
		return (NULL);
	line_pos = ft_strchr(cache, '\n');
	if (line_pos)
		new_cache = ft_strdup(line_pos + 1);
	else
		new_cache = NULL;
	free(cache);
	return (new_cache);
}

char	*fun_help(int fd, char *cache, char *buffer)
{
	ssize_t	bytes_read;

	while (!ft_strchr(cache, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(cache);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		cache = ft_strjoin(cache, buffer);
		if (!cache)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache[1024];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!cache[fd])
		cache[fd] = ft_strdup("");
	cache[fd] = fun_help(fd, cache[fd], buffer);
	if (!cache[fd])
		return (NULL);
	if (cache[fd] && *cache[fd])
	{
		line = extract_line(cache[fd]);
		cache[fd] = update_cache(cache[fd]);
		return (line);
	}
	free(cache[fd]);
	cache[fd] = NULL;
	return (NULL);
}
