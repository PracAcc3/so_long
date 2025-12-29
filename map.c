/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syedh <syedh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by syedh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static size_t	sanitize_line(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = 0;
		len--;
	}
	if (len > 0 && line[len - 1] == '\r')
	{
		line[len - 1] = 0;
		len--;
	}
	return (len);
}

static char	**grow_map(char **map, size_t n)
{
	char	**new_map;
	size_t	i;

	new_map = (char **)malloc(sizeof(char *) * (n + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

static void	map_error(char *line, int fd, char **map, const char *msg)
{
	free(line);
	close(fd);
	free_map(map);
	error_exit(msg);
}

void	read_map(t_data *d, char *file)
{
	int		fd;
	char	**map;
	size_t	n;
	char	*line;
	char	**tmp;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map");
	map = NULL;
	n = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (sanitize_line(line) == 0)
			map_error(line, fd, map, "Empty line in map");
		tmp = grow_map(map, n);
		if (!tmp)
			map_error(line, fd, map, "Malloc failed");
		map = tmp;
		map[n] = line;
		n++;
		map[n] = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	if (n == 0)
		error_exit("Empty map");
	d->map = map;
	validate_and_set(d, file);
}