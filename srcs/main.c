/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:31:26 by jdebrull          #+#    #+#             */
/*   Updated: 2025/03/14 21:06:36 by jdebrull         ###   ########.fr       */
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
		if (access(final_path, F_OK | X_OK) == 0)
			return (free_tab(tab), free(path), final_path);
		free(path);
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
		ft_putstr_fd("Command not found: ", 2);
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

char	**make_args(char *av)
{
	char	**args;
	char	*trim;

	args = malloc(sizeof(char*) * 2);
	if (!args)
		exit(1);
	trim = ft_strdup(av + 9);
	if (!trim)
	{
		free(args);
		exit(1);
	}
	args[0] = trim;
	args[1] = NULL;
	return(args);
}

void	cmd_or_path(char *av, char **env)
{
	char	**args;
	
	args = NULL;
	if (ft_strncmp("/usr/bin/", av, 9) == 0)
	{
		args = make_args(av);
		if (args && execve(av, args, env) == -1)
		{
			perror(args[0]);
			free(args[0]);
			free(args);
			exit(127);
		}
	}
	else
		command(av, env);
}

int	opening(char *file, int type)
{
	int	i;

	i = 0;
	if (type == 0)
	{
		i = open(file, O_RDONLY);
		if (i < 0)
			return (perror("Error"), -1);
	}
	else if (type == 1)
	{
		i = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (i < 0)
			return (perror("Error"), -1);
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
	dup2(fd, STDIN);
	dup2(pipe_fd[1], STDOUT);
	close(fd);
	close(pipe_fd[0]);
	cmd_or_path(av[2], env);
	
	exit(127);
}

void	parent(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = opening(av[4], 1);
	if (fd < 0)
		exit (1);
	dup2(fd, STDOUT);
	dup2(pipe_fd[0], STDIN);
	close(fd);
	close(pipe_fd[1]);
	cmd_or_path(av[3], env);
	exit(127);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		status;
	int		pipe_fd[2];

	if (ac < 5)
		exit (1);
	pipe(pipe_fd);
	pid = fork();
	if (!pid)
		child(av, pipe_fd, env);
	else
	{
		waitpid(pid, &status, 0);
		parent(av, pipe_fd, env);
	}
}