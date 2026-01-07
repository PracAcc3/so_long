/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2026/01/07 17:34:12 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	cleanup_images(t_data *d)
{
	if (!d || !d->mlx)
		return ;
	if (d->wall)
		mlx_destroy_image(d->mlx, d->wall);
	if (d->floor)
		mlx_destroy_image(d->mlx, d->floor);
	if (d->player)
		mlx_destroy_image(d->mlx, d->player);
	if (d->collect)
		mlx_destroy_image(d->mlx, d->collect);
	if (d->exit)
		mlx_destroy_image(d->mlx, d->exit);
}

static void	cleanup(t_data *d)
{
	if (!d)
		return ;
	cleanup_images(d);
	if (d->mlx && d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
	}
	free_map(d->map);
}

int	close_game(t_data *d)
{
	cleanup(d);
	exit(0);
}

void	error_game(t_data *d, const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	cleanup(d);
	exit(1);
}
