/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:01:08 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/11 19:01:10 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	if (needle[h] == '\0')
		return (0);
	while (haystack[h])
	{
		n = 0;
		while (haystack[h + n] == needle[n] && (h + n) < len)
		{
			if (haystack[h + n] == '\0' && needle[n] == '\0')
				return (1);
			n++;
		}
		if (needle[n] == '\0')
			return (1);
		h++;
	}
	return (0);
}

int	get_heredoc_fd(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open("infile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error creating heredoc file");
		exit(1);
	}
	write(1, ">> ", 3);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strnstr(line, delimiter, ft_strlen(line)))
			break ;
		write(1, ">> ", 3);
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	return (fd);
}

void	check_args(int ac)
{
	if (ac < 5)
	{
		printf("Error.\n Argumentos\n");
		exit(1);
	}
}

void	init_data(t_fd *dados, int ac, char **av)
{
	dados->start = 2;
	check_args(ac);
	if (ft_strncmp("here_doc", av[1], 8) == 0)
	{
		dados->fdin = get_heredoc_fd(av[2]);
		if (dados->fdin == -1)
		{
			perror("Error creating heredoc fileAAAAAAAAAAA");
			exit(1);
		}
		dados->start = 3;
		close(dados->fdin);
		dados->fdin = open("infile", O_RDONLY | O_CREAT);
	}
	else
		dados->fdin = open(av[1], O_RDONLY);
	dados->fdout = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (dados->fdout == -1 || dados->fdin == -1)
	{
		if (dados->fdout == -1)
			close(dados->fdin);
		perror("Error opening infile/outfile");
		exit(1);
	}
}
