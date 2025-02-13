/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:51:27 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/11 18:51:28 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h> //
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct fd
{
	int		fd1;
	int		fd2;
	int		fd_pipe[2];
	char	**cmds;
}			t_fd;

char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*substr(char *s, int index, char c, char **big);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(const char *str);
void		close_all(t_fd *fds);
t_fd		*init_data(t_fd *fds, int ac);

#endif
