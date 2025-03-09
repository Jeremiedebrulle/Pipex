/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 09:15:43 by jdebrull          #+#    #+#             */
/*   Updated: 2025/01/25 13:39:03 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_puthex(unsigned long n)
{
	int		count;

	count = 0;
	if (n > 15)
	{
		count += ft_puthex(n / 16);
		if (n % 16 > 9 && n % 16 < 16)
			count += ft_putchar(n % 16 + 87);
		else
			count += ft_putchar(n % 16 + 48);
	}
	else if (n < 16)
	{
		if (n <= 15 && n >= 10)
			count += ft_putchar(n + 87);
		else
			count += ft_putchar(n + 48);
	}
	return (count);
}

int	ft_puthexa(unsigned int n)
{
	int		count;
	char	*hexa_digit;

	count = 0;
	hexa_digit = "0123456789abcdef";
	if (n > 15)
		count += ft_puthexa(n / 16);
	count += ft_putchar(hexa_digit[n % 16]);
	return (count);
}

int	ft_puthexb(unsigned int n)
{
	int		count;
	char	*hexa_digit;

	count = 0;
	hexa_digit = "0123456789ABCDEF";
	if (n > 15)
		count += ft_puthexb(n / 16);
	count += ft_putchar(hexa_digit[n % 16]);
	return (count);
}

int	ft_format_check(va_list args, const char *format, int i)
{
	int	count;

	count = 0;
	i++;
	if (format[i] == 'c')
		count += ft_putchar((char)va_arg(args, int));
	else if (format[i] == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (format[i] == 'p')
	{
		count += ft_putstr("0x");
		count += ft_puthex((unsigned long)va_arg(args, void *));
	}
	else if (format[i] == 'd' || format[i] == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (format[i] == 'x')
		count += ft_puthexa(va_arg(args, unsigned int));
	else if (format[i] == 'X')
		count += ft_puthexb(va_arg(args, unsigned int));
	else if (format[i] == 'u')
		count += ft_unsint(va_arg(args, unsigned int));
	else if (format[i] == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	if (!format)
		return (0);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] != '%')
			count += ft_putchar(format[i]);
		else if (format[i] == '%' && format[i + 1])
		{
			count += ft_format_check(args, format, i);
			i++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
/*int	main(void)
{
	int x = 214748364;
	
	ft_printf("%d\n", ft_printf("%% qwerty %%\n %d\n", x));
	printf("%d\n", printf("%% qwerty %%\n %d\n", x));
	//ft_printf("%d\n", ft_printf("%d\n", -2147483648));
	//printf("%d\n", printf("%d\n", -2147483648));
	return (0);
}*/