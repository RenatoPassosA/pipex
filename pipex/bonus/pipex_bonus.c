/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:54:09 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/13 13:54:11 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	clear_data(char *av, char **cmd)
{
	if (ft_strncmp(av, "here_doc", ft_strlen(av)) == 0)
		unlink("infile");
	free_big(cmd);
}

static char	*apply_join(char *path, char *str)
{
	char	*temp;

	temp = path;
	path = ft_strjoin(path, str);
	free(temp);
	return (path);
}

char	*get_env_path(char **env, char *cmd)
{
	int		i;
	char	**paths;
	char	*correct_path;

	correct_path = NULL;
	i = 0;
	while (ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		paths[i] = apply_join(paths[i], "/");
		paths[i] = apply_join(paths[i], cmd);
		if (access(paths[i], F_OK) == 0)
		{
			free(correct_path);
			correct_path = ft_strdup(paths[i]);
		}
		free(paths[i]);
	}
	free(paths);
	return (correct_path);
}

void	pipe_data(char **av, t_fd data, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;
	char	**cmd;

	cmd = ft_split(av[data.start], ' ');
	status = 0;
	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		execve(get_env_path(env, cmd[0]), cmd, env);
		perror("Error.\nExecve.");
	}
	else
	{
		waitpid(pid, &status, 0);
		free_big(cmd);
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
	}
}

int	main(int ac, char **av, char **env)
{
	t_fd	data;
	pid_t	pid;
	char	**cmd;

	cmd = NULL;
	init_data(&data, ac, av);
	dup2(data.fdin, STDIN_FILENO);
	close(data.fdin);
	while (data.start < ac - 2)
	{
		pipe_data(av, data, env);
		data.start++;
	}
	dup2(data.fdout, STDOUT_FILENO);
	close(data.fdout);
	cmd = ft_split(av[data.start], ' ');
	pid = fork();
	if (pid == 0)
	{
		execve(get_env_path(env, cmd[0]), cmd, env);
		perror("Error.\nExecve 2.");
	}
	waitpid(pid, NULL, 0);
	clear_data(av[1], cmd);
	return (0);
}
