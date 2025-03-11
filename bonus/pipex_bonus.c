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

static void	pipe_child(int *pipe_fd, char *path, char **cmds, char **env)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	if (execve(path, cmds, env) == -1)
	{
		free_big(cmds);
		free(path);
		error();
	}
}

static void	pipe_parent(pid_t pid, int *pipe_fd, char *path, char **cmds)
{
	free_big(cmds);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	free(path);
}

static void	pipe_data(char **av, t_fd data, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	**cmds;
	char	*path;

	cmds = ft_split(av[data.start], ' ');
	if (pipe(pipe_fd) == -1)
		error ();
	path = get_env_path(env, cmds[0]);
	if (!path)
	{	
		free_big(cmds);
		free (path);
		exit(127);
	}
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		pipe_child(pipe_fd, path, cmds, env);
	else
	{
		waitpid(pid, NULL, 0);
		pipe_parent(pid, pipe_fd, path, cmds);
	}
}

static void	do_execve(char *path, char **cmds, char **env)
{
	if (execve(path, cmds, env) == -1)
	{
		free_big(cmds);
		free(path);
		error();
	}
}

int	main(int ac, char **av, char **env)
{
	t_fd	data;
	pid_t	pid;
	char	**cmds;
	char	*path;

	cmds = NULL;
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
	cmds = ft_split(av[data.start], ' ');
	path = get_env_path(env, cmds[0]);
	pid = fork();
	if (pid == 0)
		do_execve(path, cmds, env);
	waitpid(pid, NULL, 0);
	clear_data(av[1], cmds, path);
	return (0);
}
