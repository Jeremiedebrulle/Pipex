/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:31:26 by jdebrull          #+#    #+#             */
/*   Updated: 2025/03/09 19:28:05 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	test(char *av)
{
	int	fd;

	fd = open(av, O_WRONLY);
	if (fd == -1)
		return (1);
	ft_putstr_fd("hey, lets see if this works.\n", fd);
	close(fd);
	return (0);
}

int	main(int ac, char **av)
{
	char	*cmd;
	pid_t	pid;
	char	*args[] = {"ls", "-l", NULL};

	cmd = "/bin/ls";
	pid = fork();
	if (pid < 0)
	{
		perror ("Fork failed");
		return (1);
	}
	else  if (pid == 0)
	{
		if (ac != 5)
			return (0);
		else
		{
			if (access(av[1], R_OK) != -1 && access(av[4], W_OK) != -1)
			{
				ft_printf("file1 is readable and file2 is writable!\n");
				test(av[4]);
			}
			else
				ft_printf("Error!\n");
			if (ft_strncmp(av[2], "ls", 2) == 0)
			{
				execve(cmd, args, NULL);	//might want to fork here i guess??
				perror("execve failed");
				return (1);
			}
		}
	}
	else
	{
		wait(NULL);
		ft_printf("Child process completed.\n");
	}
	return (0);
}