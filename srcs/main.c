/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:31:26 by jdebrull          #+#    #+#             */
/*   Updated: 2025/03/13 19:01:50 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_tab(char	**tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

char	*get_path(char	*cmd, char **env)
{
	int		i;
	char	*path;
	char	*final_path;
	char	**tab;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	tab = ft_split(env[i] + 5, ':');
	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		path = ft_strjoin(tab[i], "/");
		final_path = ft_strjoin(path, cmd);
		free(path);
		if (access(final_path, F_OK | X_OK) == 0)
			return (free_tab(tab), free(path), final_path);
		free(final_path);
		i++;
	}
	return(free_tab(tab), NULL);
}

void	command(char *cmd, char **env)
{
	char	**tab;
	char	*path;

	tab = ft_split(cmd, ' ');
	if (!tab || !tab[0])
	{
		free_tab(tab);
		exit (127);
	}
	path = get_path(tab[0], env);
	if (!path)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(tab[0], 2);
		free_tab(tab);
		exit (127);
	}
	if (execve(path, tab, env) == -1)
	{
		perror(tab[0]);
		free_tab(tab);
		free(path);
		exit(127);
	}
}

int	opening(char *file, int type)
{
	int	i;

	i = 0;
	if (type == 0)
	{
		i = open(file, O_RDONLY, 0644);
		if (i < 0)
			return (perror("error opening file for reading"), -1);
	}
	else if (type == 1)
	{
		i = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (i < 0)
			return (perror("error opening file for reading"), -1);
	}
	else
		return (-1);
	return (i);
}

void	child(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = opening(av[1], 0);
	if (fd < 0)
		exit (1);
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	command(av[1], env);
}

void	parent(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = opening(av[1], 0);
	if (fd < 0)
		exit (1);
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	command(av[4], env);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (ac < 5)
		exit (-1);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
		child(av, pipe_fd, env);
	parent(av, pipe_fd, env);
}