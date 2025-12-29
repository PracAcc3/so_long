/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_counts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syedh <syedh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by syedh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_counts(t_data *d, int p_count, int e_count, int c_count)
{
	if (p_count != 1)
		error_game(d, "No start");
	if (e_count != 1)
		error_game(d, "No exit");
	if (c_count < 1)
		error_game(d, "No collectible");
	d->c_left = c_count;
}

static void	count_tile(t_data *d, int x, int y, int *counts)
{
	char	c;

	c = d->map[y][x];
	if (c == TILE_PLAYER)
	{
		counts[0]++;
		d->px = x;
		d->py = y;
	}
	else if (c == TILE_EXIT)
		counts[1]++;
	else if (c == TILE_COLLECT)
		counts[2]++;
	else if (c != TILE_FLOOR && c != TILE_WALL)
		error_game(d, "Invalid character in map");
}

void	validate_counts(t_data *d)
{
	int	x;
	int	y;
	int	counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	y = 0;
	while (y < d->h)
	{
		x = 0;
		while (x < d->w)
		{
			count_tile(d, x, y, counts);
			x++;
		}
		y++;
	}
	check_counts(d, counts[0], counts[1], counts[2]);
}
