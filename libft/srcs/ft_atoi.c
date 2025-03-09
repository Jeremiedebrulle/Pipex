/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:33:24 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/27 17:42:18 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	n;
	int					sign;

	i = 0;
	n = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		n = n * 10 + (str[i++] - 48);
	}
	if (n > 9223372036854775807 && sign < 0)
		return (0);
	if (n > 9223372036854775807 && sign > 0)
		return (-1);
	return ((int)n * sign);
}
/* int	main(void)
{
	//char c[] = "2147483648";
	// char c[] = "2848381155";
	char c[] = "00";
	printf("%d\n", ft_atoi(c));
	printf("%d\n", atoi(c));
} */