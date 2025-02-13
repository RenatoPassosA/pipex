/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:51:37 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/11 18:51:38 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
		counter++;
	return (counter);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	close_all(t_fd *fds)
{
	close(fds->fd1);
	close(fds->fd2);
	close(fds->fd_pipe[0]);
	close(fds->fd_pipe[0]);
}

t_fd	*init_data(t_fd *fds, int ac)
{
	if (ac != 5)
	{
		printf("Error.\n Argumentos\n");
		exit(1);
	}
	fds = (t_fd *)malloc(sizeof(t_fd));
	if (!fds)
		exit(1);
	fds->fd1 = 0;
	fds->fd2 = 0;
	fds->fd_pipe[0] = 0;
	fds->fd_pipe[1] = 0;
	if (pipe(fds->fd_pipe) == -1)
	{
		free(fds);
		exit(1);
	}
	return (fds);
}
