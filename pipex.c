/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:51:12 by rpassos-          #+#    #+#             */
/*   Updated: 2025/02/11 18:51:14 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_env_path(char **env, char *cmd)
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
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK) == 0)
			return (get_access(paths, full_path));
		free(full_path);
	}
	free_big(paths);
	perror("command not found");
	return (NULL);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

static void	child_process(int *pipe_fd, char *cmd, char **env, char *av)
{
	int		fd;
	char	**cmds;
	char	*path;

	fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
		error();
	cmds = ft_split(cmd, ' ');
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(pipe_fd[1]);
	path = get_env_path(env, cmds[0]);
	if (!path)
	{
		free_big(cmds);
		free (path);
		exit(127);
	}
	if (execve(path, cmds, env) == -1)
	{
		free_big(cmds);
		free(path);
		error();
	}
}

static void	parent_process(int *pipe_fd, char *cmd, char **env, char *av)
{
	int		fd;
	char	**cmds;
	char	*path;

	fd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error();
	cmds = ft_split(cmd, ' ');
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipe_fd[0]);
	path = get_env_path(env, cmds[0]);
	if (!path)
	{
		free_big(cmds);
		free (path);
		exit(127);
	}
	if (execve(path, cmds, env) == -1)
	{
		free_big(cmds);
		free(path);
		error();
	}
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (ac != 5)
		error();
	if (pipe(pipe_fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error ();
	if (pid == 0)
		child_process(pipe_fd, av[2], env, av[1]);
	waitpid(pid, NULL, 0);
	parent_process(pipe_fd, av[3], env, av[4]);
	return (0);
}
