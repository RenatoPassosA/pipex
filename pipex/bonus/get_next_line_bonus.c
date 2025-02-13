/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:45:53 by rpassos-          #+#    #+#             */
/*   Updated: 2024/11/08 15:23:12 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "pipex_bonus.h"

static char	*set_line(char **store)
{
	int		i;
	char	*line;
	char	*temp;

	line = NULL;
	i = 0;
	if (ft_strchr(*store, '\n'))
	{
		while (store[0][i] != '\n')
			i++;
		i++;
		line = ft_substr(*store, 0, i);
		temp = *store;
		*store = ft_substr(*store, i, ft_strlen(*store) - i);
		free(temp);
	}
	else
	{
		line = *store;
		*store = NULL;
	}
	return (line);
}

static int	check_empty(char **store, char *buffer, int r_return)
{
	if (r_return < 0 || !store[0] || (!r_return && store[0][0] == '\0'))
	{
		free(buffer);
		free(*store);
		*store = NULL;
		return (1);
	}
	return (0);
}

static char	*read_line(int fd, char **store)
{
	char	*buffer;
	int		read_return;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_return = read(fd, buffer, BUFFER_SIZE);
	if (read_return == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[read_return] = '\0';
	while (read_return > 0)
	{
		*store = ft_strjoin(*store, buffer);
		if (ft_strchr(*store, '\n'))
			break ;
		read_return = read(fd, buffer, BUFFER_SIZE);
		buffer[read_return] = '\0';
	}
	if (check_empty(store, buffer, read_return) == 1)
		return (NULL);
	free(buffer);
	return (set_line(store));
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, &store);
	if (!line)
		return (NULL);
	if (store && store[0] == '\0')
	{
		free(store);
		store = NULL;
	}
	return (line);
}
