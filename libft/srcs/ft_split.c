/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:51:08 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/27 17:26:09 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	strs_count(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_word(const char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*free_tab(char **strs, int n_words)
{
	int	i;

	i = 0;
	if (!strs)
		return (NULL);
	while (i < n_words)
		free(strs[i++]);
	free(strs);
	return (NULL);
}

static char	**ft_makesplit(const char *s, char **strs, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			strs[j] = ft_word(&s[i], c);
			if (!strs[j])
				return (free_tab(strs, j));
			while (s[i] && s[i] != c)
				i++;
			j++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	strs[j] = 0;
	return (strs);
}

char	**ft_split(const char *s, char c)
{
	char	**strs;

	if (!s)
		return (NULL);
	strs = malloc(sizeof(*strs) * (strs_count((char *)s, c) + 1));
	if (!strs)
		return (NULL);
	strs = ft_makesplit((const char *)s, strs, c);
	return (strs);
}
/*int	main(void)
{
	int		i;
	char	*str = "xxxxxxxxhello!";
	char	charset = 'x';
	char	**tab;

	tab = ft_split(str, charset);
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}*/