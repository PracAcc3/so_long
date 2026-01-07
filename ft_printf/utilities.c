/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:01:21 by synoshah          #+#    #+#             */
/*   Updated: 2025/08/21 14:42:34 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;
	int	result;

	if (!s)
		s = "(null)";
	i = 0;
	while (*s)
	{
		result = ft_putchar(*s++);
		if (result < 0)
			return (result);
		i += result;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	long	nbr;
	int		count;
	int		result;

	nbr = n;
	count = 0;
	if (nbr < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		count++;
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		result = ft_putnbr(nbr / 10);
		if (result < 0)
			return (result);
		count += result;
	}
	result = ft_putchar((nbr % 10) + '0');
	return (count + result);
}

int	ft_unsigned(unsigned int n)
{
	int	count;
	int	result;

	count = 0;
	if (n >= 10)
	{
		result = ft_unsigned(n / 10);
		if (result < 0)
			return (result);
		count += result;
	}
	result = ft_putchar((n % 10) + '0');
	return (count + result);
}
