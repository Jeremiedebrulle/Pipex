/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:12:10 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/25 13:38:23 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen == 0)
	{
		ft_memcpy(dst, src, 1);
		return (0);
	}
	if (dstsize == 0)
		return (srclen);
	if (srclen < dstsize)
		ft_memcpy(dst, src, srclen + 1);
	else
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srclen);
}

/*int	main(void)
{
	char dst[50];
	//char src[] = "";
	printf("%zu\n", ft_strlcpy(dst, "lorem", 15));
	printf("%s\n", dst);
	//printf("%lu\n", strlcpy(dst, "", 15));
	//printf("%s\n", dst);
}*/