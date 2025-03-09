/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:36:55 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/25 13:37:49 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_substr_gnl(char *line_buffer, int start, int len)
{
	int		i;
	char	*substr;

	if (!line_buffer)
		return (NULL);
	if (start > ft_strlen_gnl(line_buffer))
		return (malloc(1));
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && line_buffer[start])
		substr[i++] = line_buffer[start++];
	substr[i] = '\0';
	return (substr);
}

static char	*ft_line(char *line_buffer)
{
	int		i;
	int		len;
	char	*stash;

	i = 0;
	len = ft_strlen_gnl(line_buffer) - i - 1;
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	stash = ft_substr_gnl(line_buffer, i + 1, len);
	if (!stash || *stash == 0)
		return (ft_free(&stash), NULL);
	line_buffer[i + 1] = 0;
	return (stash);
}

static char	*ft_fill_buffer(int fd, char *stash, char *buffer)
{
	int		n_bytes;

	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes < 0)
			return (ft_free(&stash), NULL);
		else if (n_bytes == 0)
			break ;
		buffer[n_bytes] = 0;
		if (!stash)
			stash = ft_strdup_gnl("");
		stash = ft_strjoin_gnl(stash, buffer, n_bytes);
		if (!stash)
			return (NULL);
		if (ft_chrcheck(buffer, '\n'))
			break ;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (BUFFER_SIZE > MAX_BUFFER_SIZE)
		return (NULL);
	stash = ft_fill_buffer(fd, stash, buffer);
	if (!stash)
		return (NULL);
	line = ft_strdup_gnl(stash);
	ft_free(&stash);
	stash = ft_line(line);
	return (line);
}

/*int	main(void)
{
	int		fd;
	int 	i = 0;
	char 	*line;

	fd = open("text.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line)
			printf("%s\n - %d\n", line, ++i);
		else
			break ;
		free(line);
		line = NULL;
	}
	close(fd);
}*/