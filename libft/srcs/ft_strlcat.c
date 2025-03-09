/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:25:28 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/25 13:38:28 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dstlen;
	unsigned int	srclen;

	i = 0;
	dstlen = ft_strlen(dst);
	j = dstlen;
	srclen = ft_strlen(src);
	if (size == 0 || size <= dstlen)
		return (srclen + size);
	while (src[i] && i < size - dstlen - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (srclen + dstlen);
}

/*int	main(void)
{
	char dst[11] = "a";
	char src[] = "lorem ipsum";
	printf("%lu\n", ft_strlcat(dst, src, 15));
	printf("%s\n", dst);
	//printf("%lu\n", strlcat(dst, src, 15));
	//printf("%s\n", dst);
}*/