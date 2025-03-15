/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:29:57 by jdebrull          #+#    #+#             */
/*   Updated: 2025/03/15 14:33:15 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

# define STDIN 0
# define STDOUT 1

void	args_handler(char **av, char **env);
void	parent(char **av, int *pipe_fd, char **env);
void	child(char **av, int *pipe_fd, char **env);
int		opening(char *file, int type);
void	free_tab(char **tab);
void	cmd_or_path(char *av, char **env);
void	command(char *cmd, char **env);
char	*get_path(char	*cmd, char **env);
char	*crea_path(char *final_path, char *path, char *cmd, char **tab);

#endif