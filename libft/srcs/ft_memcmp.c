/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:18:12 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/25 13:39:16 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while (i < n && tmp1[i] == tmp2[i])
		i++;
	if (n == i)
		return (0);
	return ((unsigned char)tmp1[i] - (unsigned char)tmp2[i]);
}
/*int	main(void)
{
	char *s1 = NULL;
	char s2[] = {18};

	printf("%d\n", ft_memcmp(s1, s2, 2));
	printf("%d\n", ft_memcmp(s1, s2, 4));
	printf("%d\n", ft_memcmp(s1, s2, 8));
	printf("%d\n", memcmp(s1, s2, 2));
	printf("%d\n", memcmp(s1, s2, 4));
	printf("%d\n", memcmp(s1, s2, 8));
}*/