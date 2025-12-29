/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syedh <syedh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by syedh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_tile(t_data *d, void *img, int x, int y)
{
	if (!img)
		return ;
	mlx_put_image_to_window(d->mlx, d->win, img, x * TILE, y * TILE);
}

void	draw_map(t_data *d)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < d->h)
	{
		x = 0;
		while (x < d->w)
		{
			c = d->map[y][x];
			if (c == TILE_WALL)
				put_tile(d, d->wall, x, y);
			else
				put_tile(d, d->floor, x, y);
			if (c == TILE_COLLECT)
				put_tile(d, d->collect, x, y);
			else if (c == TILE_EXIT)
				put_tile(d, d->exit, x, y);
			else if (c == TILE_PLAYER)
				put_tile(d, d->player, x, y);
			x++;
		}
		y++;
	}
}
