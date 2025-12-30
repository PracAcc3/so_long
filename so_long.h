/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syedh <syedh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by syedh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>

# include "ft_printf.h"
# include "get_next_line.h"

# define TILE 32
# define TILE_FLOOR '0'
# define TILE_WALL '1'
# define TILE_PLAYER 'P'
# define TILE_COLLECT 'C'
# define TILE_EXIT 'E'

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		w;
	int		h;
	int		px;
	int		py;
	int		c_left;
	int		moves;
	void	*wall;
	void	*floor;
	void	*player;
	void	*collect;
	void	*exit;
}	t_data;

void	read_map(t_data *d, char *file);
void	validate_and_set(t_data *d, const char *file);
void	draw_map(t_data *d);
int		key_hook(int key, t_data *d);
int		close_game(t_data *d);
void	error_game(t_data *d, const char *msg);
void	error_exit(const char *msg);
void	free_map(char **map);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(const char *s, int fd);

#endif
