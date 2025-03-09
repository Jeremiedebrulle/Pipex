/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:46:29 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/25 13:38:48 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	a;

	i = 0;
	a = (char)c;
	if (a == '\0')
	{
		i = ft_strlen(s);
		return ((char *)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == a)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
/*int	main(void)
{
	char s[] = "qw0ey12rtyaui'opwryipoitei";
	char a = {-33};
	printf("%s\n", ft_strchr(s, a));
	printf("%s\n", strchr(s, a));
}*/