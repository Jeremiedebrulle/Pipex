/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:31:26 by jdebrull          #+#    #+#             */
/*   Updated: 2025/03/15 17:33:31 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	opening(char *file, int type)
{
	int	i;

	i = 0;
	if (type == 0)
	{
		i = open(file, O_RDONLY);
		if (i < 0)
			return (perror(file), -1);
	}
	else if (type == 1)
	{
		i = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (i < 0)
			return (perror(file), -1);
	}
	else
		return (-1);
	return (i);
}

void	child(char **av, int *pipe_fd, char **env)
{
	int	fd_in;

	fd_in = opening(av[1], 0);
	if (fd_in < 0)
		exit (1);
	dup2(fd_in, STDIN);
	dup2(pipe_fd[1], STDOUT);
	close(fd_in);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	cmd_or_path(av[2], env);
	exit(1);
}

void	parent(char **av, int *pipe_fd, char **env)
{
	int	fd_out;

	fd_out = opening(av[4], 1);
	if (fd_out < 0)
		exit (1);
	dup2(fd_out, STDOUT);
	dup2(pipe_fd[0], STDIN);
	close(fd_out);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	cmd_or_path(av[3], env);
	exit(1);
}

void	args_handler(char **av, char **env)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		perror("Error: pipe failed");
		exit (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error: fork failed");
		exit(1);
	}
	if (!pid)
		child(av, pipe_fd, env);
	else
	{
		waitpid(pid, &status, 0);
		parent(av, pipe_fd, env);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
	{
		ft_putstr_fd("Error number of args", 2);
		exit (1);
	}
	else if (ac == 5)
		args_handler(av, env);
	return (0);
}
