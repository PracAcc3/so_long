/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syedh <syedh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by syedh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*img_addr(void *img, int *meta)
{
	return (mlx_get_data_addr(img, &meta[0], &meta[1], &meta[2]));
}

static unsigned int	*pixel_ptr(char *addr, int *meta, int x, int y)
{
	return ((unsigned int *)(addr + (y * meta[1]) + (x * (meta[0] / 8))));
}

static void	bake_floor_into_sprite(t_data *d, void *sprite)
{
	char			*addr[2];
	int				meta[2][3];
	int				p[2];
	unsigned int	key;

	if (!d || !d->floor || !sprite)
		return ;
	addr[0] = img_addr(sprite, meta[0]);
	addr[1] = img_addr(d->floor, meta[1]);
	if (!addr[0] || !addr[1] || meta[0][0] != 32 || meta[1][0] != 32)
		return ;
	key = *(unsigned int *)addr[0];
	p[1] = 0;
	while (p[1] < TILE)
	{
		p[0] = 0;
		while (p[0] < TILE)
		{
			if (*pixel_ptr(addr[0], meta[0], p[0], p[1]) == key)
				*pixel_ptr(addr[0], meta[0], p[0], p[1]) = *pixel_ptr(addr[1],
					meta[1], p[0], p[1]);
			p[0]++;
		}
		p[1]++;
	}
}

static void	load_textures(t_data *d)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	d->wall = mlx_xpm_file_to_image(d->mlx,
			"textures/wall.xpm", &w, &h);
	d->floor = mlx_xpm_file_to_image(d->mlx,
			"textures/floor.xpm", &w, &h);
	d->player = mlx_xpm_file_to_image(d->mlx,
			"textures/character.xpm", &w, &h);
	d->collect = mlx_xpm_file_to_image(d->mlx,
			"textures/collectable.xpm", &w, &h);
	d->exit = mlx_xpm_file_to_image(d->mlx,
			"textures/exit.xpm", &w, &h);
	if (!d->wall || !d->floor || !d->player || !d->collect
		|| !d->exit)
		error_game(d, "Failed to load textures");
	bake_floor_into_sprite(d, d->player);
	bake_floor_into_sprite(d, d->collect);
	bake_floor_into_sprite(d, d->exit);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc != 2)
		error_exit("Usage: ./so_long <map.ber>");
	d = (t_data){0};
	read_map(&d, argv[1]);
	d.mlx = mlx_init();
	if (!d.mlx)
		error_game(&d, "mlx_init failed");
	d.win = mlx_new_window(d.mlx,
			d.w * TILE, d.h * TILE, "so_long");
	if (!d.win)
		error_game(&d, "mlx_new_window failed");
	load_textures(&d);
	draw_map(&d);
	mlx_key_hook(d.win, key_hook, &d);
	mlx_hook(d.win, 17, 0, close_game, &d);
	mlx_loop(d.mlx);
	return (0);
}
