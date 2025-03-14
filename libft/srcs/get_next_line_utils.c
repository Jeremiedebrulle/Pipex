/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:26:36 by jdebrull          #+#    #+#             */
/*   Updated: 2025/03/10 15:30:39 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_free(char **str)
{
	if (!*str || !str)
		return ;
	free(*str);
	*str = NULL;
}

char	*ft_strdup_gnl(char *s)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * (ft_strlen_gnl(s) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_chrcheck(char *buffer, char c)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *stash, char *buffer, int n_bytes)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	if (!stash || !buffer)
	{
		return (ft_free(&stash), NULL);
		stash[0] = '\0';
	}
	len = ft_strlen_gnl(stash);
	join = malloc(sizeof(char) * (len + n_bytes + 1));
	if (!join)
		return (ft_free(&stash), NULL);
	i = -1;
	while (++i < len)
		join[i] = stash[i];
	j = 0;
	while (j < n_bytes)
		join[i++] = buffer[j++];
	join[i] = '\0';
	ft_free(&stash);
	return (join);
}
