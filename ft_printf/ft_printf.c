/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:19:10 by synoshah          #+#    #+#             */
/*   Updated: 2025/08/21 15:51:11 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format(char specifier, va_list ap)
{
	int	count;

	if (specifier == 'c')
		return (ft_putchar(va_arg(ap, int)));
	else if (specifier == 's')
		return (ft_putstr(va_arg(ap, char *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(ap, int)));
	else if (specifier == 'u')
		return (ft_unsigned(va_arg(ap, unsigned int)));
	else if (specifier == 'x' || specifier == 'X')
		return (ft_hex(va_arg(ap, unsigned int), specifier));
	else if (specifier == 'p')
	{
		count = ft_putstr("0x");
		if (count < 0)
			return (count);
		return (count + ft_hex((unsigned long long)va_arg(ap, void *), 'p'));
	}
	else if (specifier == '%')
		return (ft_putchar('%'));
	return (0);
}

static int	edge_case(int *count, int result)
{
	if (result < 0)
		return (result);
	*count += result;
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		index;
	int		count;
	int		result;

	index = 0;
	count = 0;
	va_start(ap, s);
	while (s[index])
	{
		if (s[index] == '%')
			result = format(s[++index], ap);
		else
			result = ft_putchar(s[index]);
		if (edge_case(&count, result))
			return (result);
		index++;
	}
	va_end(ap);
	return (count);
}
