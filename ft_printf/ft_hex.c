/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:58:40 by synoshah          #+#    #+#             */
/*   Updated: 2025/08/21 15:24:22 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex(unsigned long n, char format)
{
	char	*base;
	int		count;
	int		res;

	if (format == 'x')
		base = "0123456789abcdef";
	else if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		res = ft_hex(n / 16, format);
		if (res < 0)
			return (res);
		count += res;
	}
	res = ft_putchar(base[n % 16]);
	return (count + res);
}
