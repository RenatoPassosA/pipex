/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:01:01 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/11 19:01:03 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct fd
{
	int			fdin;
	int			fdout;
	int			start;
	struct fd	*next;
}				t_fd;

char			**ft_split(char const *s, char c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strjoin(char *s1, char *s2);
size_t			ft_strlen(const char *str);
void			init_data(t_fd *dados, int ac, char **av);
char			*get_next_line(int fd);
int				ft_strnstr(char *haystack, char *needle, size_t len);
char			*get_env_path(char **env, char *cmd);
char			*ft_strdup(char *str);
void			free_big(char **big);
void			error(void);
void			clear_data(char *av, char **cmd, char *path);

#endif
