/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:35:49 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/19 14:35:52 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_access(char **paths, char *full_path)
{
	free_big(paths);
	return (full_path);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	clear_data(char *av, char **cmd, char *path)
{
	if (ft_strncmp(av, "here_doc", ft_strlen(av)) == 0)
		unlink("infile");
	free_big(cmd);
	free(path);
}

char	*get_env_path(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*temp;
	char	*full_path;

	i = 0;
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	while (ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
			return (get_access(paths, full_path));
		free(full_path);
		i++;
	}
	free_big(paths);
	error();
	return (NULL);
}
