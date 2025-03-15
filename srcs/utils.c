/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:47:09 by jdebrull          #+#    #+#             */
/*   Updated: 2025/03/15 17:09:15 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_tab(char **tab)
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

char	*crea_path(char *final_path, char *path, char *cmd, char **tab)
{
	int		i;

	i = -1;
	final_path = NULL;
	while (tab[++i])
	{
		path = ft_strjoin(tab[i], "/");
		if (!path)
			return (ft_putstr_fd("Error with memory allocation", 2), NULL);
		final_path = ft_strjoin(path, cmd);
		free(path);
		if (!final_path)
			return (ft_putstr_fd("Error with memory allocation", 2), NULL);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
		final_path = NULL;
	}
	return (NULL);
}

char	*get_path(char	*cmd, char **env)
{
	int		i;
	char	*path;
	char	*final_path;
	char	**env_tab;

	i = 0;
	path = NULL;
	final_path = NULL;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	env_tab = ft_split(env[i] + 5, ':');
	if (!env_tab)
		return (ft_putstr_fd("Error with memory allocation", 2), NULL);
	final_path = crea_path(final_path, path, cmd, env_tab);
	if (!final_path)
		return (free_tab(env_tab), NULL);
	return (free_tab(env_tab), final_path);
}

void	command(char *cmd, char **env)
{
	char	**cmd_tab;
	char	*path;

	cmd_tab = ft_split(cmd, ' ');
	if (!cmd_tab || !cmd_tab[0])
	{
		ft_putstr_fd("Error with memory allocation", 2);
		free_tab(cmd_tab);
		exit (1);
	}
	path = get_path(cmd_tab[0], env);
	if (!path)
	{
		ft_putstr_fd("Error command not found: ", 2);
		ft_putendl_fd(cmd_tab[0], 2);
		free_tab(cmd_tab);
		exit (1);
	}
	if (execve(path, cmd_tab, env) == -1)
	{
		perror(cmd_tab[0]);
		free_tab(cmd_tab);
		free(path);
		exit(1);
	}
}

void	cmd_or_path(char *av, char **env)
{
	char	**args;

	args = ft_split(av, ' ');
	if (!args)
	{
		ft_putstr_fd("Error with memory allocation", 2);
		exit (1);
	}
	if (access(args[0], F_OK | X_OK) == 0)
	{
		if (args && execve(args[0], args, env) == -1)
		{
			perror(args[0]);
			free_tab(args);
			exit(1);
		}
	}
	else
		free_tab(args);
	command(av, env);
}
