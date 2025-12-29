/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syedh <syedh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by syedh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nb;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd((int)(nb / 10), fd);
	c = (char)('0' + (nb % 10));
	write(fd, &c, 1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t					i;
	unsigned const char	*a;
	unsigned const char	*b;

	if (!s1 || !s2)
		return (1);
	a = (unsigned const char *)s1;
	b = (unsigned const char *)s2;
	i = 0;
	while (i < n && (a[i] || b[i]))
	{
		if (a[i] != b[i])
			return ((int)a[i] - (int)b[i]);
		i++;
	}
	return (0);
}

void	error_exit(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(1);
}

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
