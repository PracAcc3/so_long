/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2026/01/07 17:33:08 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_extension(t_data *d, const char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + (len - 4), ".ber", 4) != 0)
		error_game(d, "Map must end with .ber");
}

static void	set_map_size(t_data *d)
{
	d->h = 0;
	while (d->map[d->h])
		d->h++;
	if (d->h == 0)
		error_game(d, "Empty map");
	d->w = (int)ft_strlen(d->map[0]);
	if (d->w == 0)
		error_game(d, "Empty map line");
}

static void	check_rectangular(t_data *d)
{
	int	y;

	y = 0;
	while (y < d->h)
	{
		if ((int)ft_strlen(d->map[y]) != d->w)
			error_game(d, "Map must be rectangular");
		y++;
	}
}

static void	check_walls(t_data *d)
{
	int	x;
	int	y;

	x = 0;
	while (x < d->w)
	{
		if (d->map[0][x] != TILE_WALL)
			error_game(d, "Map must be surrounded by walls");
		if (d->map[d->h - 1][x] != TILE_WALL)
			error_game(d, "Map must be surrounded by walls");
		x++;
	}
	y = 0;
	while (y < d->h)
	{
		if (d->map[y][0] != TILE_WALL)
			error_game(d, "Map must be surrounded by walls");
		if (d->map[y][d->w - 1] != TILE_WALL)
			error_game(d, "Map must be surrounded by walls");
		y++;
	}
}

void	validate_setup(t_data *d, const char *file)
{
	check_extension(d, file);
	set_map_size(d);
	check_rectangular(d);
	check_walls(d);
	validate_counts(d);
}
