/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2026/01/07 19:35:54 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*str_dup_or_null(const char *src)
{
	char		*dst;
	size_t		i;
	size_t		len;

	len = ft_strlen(src);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static char	**map_dup_or_die(t_data *d)
{
	char	**copy;
	int		y;
	int		i;

	copy = (char **)malloc(sizeof(char *) * (d->h + 1));
	if (!copy)
		error_game(d, "Malloc failed");
	y = 0;
	while (y < d->h)
	{
		copy[y] = str_dup_or_null(d->map[y]);
		if (!copy[y])
		{
			i = 0;
			while (i < y)
				free(copy[i++]);
			free(copy);
			error_game(d, "Malloc failed");
		}
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

static void	flood_fill(char **m, t_data *d, int x, int y)
{
	if (x < 0 || y < 0 || x >= d->w || y >= d->h)
		return ;
	if (m[y][x] == TILE_WALL || m[y][x] == 'V')
		return ;
	m[y][x] = 'V';
	flood_fill(m, d, x + 1, y);
	flood_fill(m, d, x - 1, y);
	flood_fill(m, d, x, y + 1);
	flood_fill(m, d, x, y - 1);
}

static void	check_reachable(t_data *d, char **visited)
{
	int		x;
	int		y;
	char	tile;

	y = 0;
	while (y < d->h)
	{
		x = 0;
		while (x < d->w)
		{
			tile = d->map[y][x];
			if (visited[y][x] != 'V')
			{
				if (tile == TILE_COLLECT)
					error_game(d, "No path to every collectibles");
				if (tile == TILE_EXIT)
					error_game(d, "No path to exit");
			}
			x++;
		}
		y++;
	}
}

void	validate_path(t_data *d)
{
	char	**copy;

	copy = map_dup_or_die(d);
	flood_fill(copy, d, d->px, d->py);
	check_reachable(d, copy);
	free_map(copy);
}
