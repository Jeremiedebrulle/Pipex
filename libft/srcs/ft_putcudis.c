/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcudis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:54:48 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/25 13:38:56 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putchar(char c)
{
	int	count;

	count = write(1, &c, 1);
	return (count);
}

int	ft_putstr(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (count += ft_putstr("(null)"));
	while (str[i])
	{
		count += ft_putchar(str[i]);
		i++;
	}
	return (count);
}

int	ft_putnbr(int n)
{
	long	nbr;
	int		count;

	nbr = n;
	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr("-2147483648");
		return (count);
	}
	if (nbr < 0)
	{
		count += ft_putchar(45);
		nbr *= -1;
	}
	if (nbr > 9)
	{
		count += ft_putnbr(nbr / 10);
		count += ft_putchar(nbr % 10 + 48);
	}
	else
		count += ft_putchar(nbr + 48);
	return (count);
}

int	ft_unsint(unsigned int n)
{
	long	nbr;
	int		count;

	nbr = n;
	count = 0;
	if (nbr > 9)
	{
		count += ft_unsint(nbr / 10);
		count += ft_putchar(nbr % 10 + 48);
	}
	else if (nbr <= 9)
		count += ft_putchar(nbr + 48);
	return (count);
}
