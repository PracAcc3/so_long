/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syedh <syedh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by syedh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*dup_line(const char *src)
{
	char	*dst;
	int		i;
	int		len;

	len = (int)ft_strlen(src);
	dst = (char *)malloc((size_t)len + 1);
	if (!dst)
		error_exit("Malloc failed");
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

static char	**dup_map(char **map, int h)
{
	char	**copy;
	int		y;

	copy = (char **)malloc(sizeof(char *) * (h + 1));
	if (!copy)
		error_exit("Malloc failed");
	y = 0;
	while (y < h)
	{
		copy[y] = dup_line(map[y]);
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

static void	flood_fill(char **m, int w, int h, int x, int y)
{
	if (x < 0 || y < 0 || x >= w || y >= h)
		return ;
	if (m[y][x] == TILE_WALL || m[y][x] == 'V')
		return ;
	m[y][x] = 'V';
	flood_fill(m, w, h, x + 1, y);
	flood_fill(m, w, h, x - 1, y);
	flood_fill(m, w, h, x, y + 1);
	flood_fill(m, w, h, x, y - 1);
}

void	validate_path(t_data *d)
{
	char	**copy;
	int		x;
	int		y;

	copy = dup_map(d->map, d->h);
	flood_fill(copy, d->w, d->h, d->px, d->py);
	y = 0;
	while (y < d->h)
	{
		x = 0;
		while (x < d->w)
		{
			if (d->map[y][x] == TILE_COLLECT && copy[y][x] != 'V')
				error_game(d, "No valid path to all collectibles");
			if (d->map[y][x] == TILE_EXIT && copy[y][x] != 'V')
				error_game(d, "No valid path to exit");
			x++;
		}
		y++;
	}
	free_map(copy);
}
