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

	i = 0;
	while (ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		temp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		free(temp);
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (NULL);
}

static int	open_files(t_fd *fds, char *av1, char *av4)
{
	fds->fd1 = open(av1, O_RDONLY);
	if (fds->fd1 == -1)
	{
		perror("Error opening infile");
		return (0);
	}
	fds->fd2 = open(av4, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fds->fd2 == -1)
	{
		close(fds->fd1);
		perror("Error opening outfile");
		return (0);
	}
	return (1);
}

static void	child_process(t_fd *fds, char *cmd, char **env)
{
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	close(fds->fd_pipe[0]);
	dup2(fds->fd1, STDIN_FILENO);
	dup2(fds->fd_pipe[1], STDOUT_FILENO);
	close(fds->fd1);
	close(fds->fd_pipe[1]);
	execve(get_env_path(env, cmds[0]), cmds, env);
	perror("Error.\nExecve 1.");
}

static void	parent_process(t_fd *fds, char *cmd, char **env)
{
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	close(fds->fd_pipe[1]);
	dup2(fds->fd_pipe[0], STDIN_FILENO);
	dup2(fds->fd2, STDOUT_FILENO);
	close(fds->fd_pipe[0]);
	close(fds->fd2);
	execve(get_env_path(env, cmds[0]), cmds, env);
	perror("Error.\nExecve 2.");
}

int	main(int ac, char **av, char **env)
{
	t_fd	*fds;
	pid_t	pid;
	pid_t	pid2;
	int		status;

	fds = NULL;
	fds = init_data(fds, ac);
	if (!open_files(fds, av[1], av[4]))
		return (2);
	pid = fork();
	if (pid == -1)
	{
		close_all(fds);
		return (4);
	}
	if (pid == 0)
		child_process(fds, av[2], env);
	pid2 = fork();
	if (pid2 == 0)
		parent_process(fds, av[3], env);
	waitpid(pid, &status, 0);
	free(fds);
	return (0);
}
