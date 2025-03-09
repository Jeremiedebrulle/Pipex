/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:52:21 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/25 13:38:03 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_setcheck(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*dst;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_setcheck(set, s1[i]))
		i++;
	j = ft_strlen(s1) - 1;
	while (j >= 0 && ft_setcheck(set, s1[j]))
		j--;
	if (j < i)
		return (ft_strdup(""));
	dst = malloc(sizeof(char) * (j - i + 2));
	if (!dst)
		return (NULL);
	if (s1[i] == '\0')
		return (dst);
	k = 0;
	while (i <= j)
		dst[k++] = s1[i++];
	dst[k] = 0;
	return (dst);
}
/*int	main(void)
{
	printf("%s\n", ft_strtrim("", ""));
	return (0);
}*/