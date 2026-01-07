/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2026/01/07 17:36:49 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_textures(t_data *d)
{
	int	w;
	int	h;

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
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc != 2)
		error_exit("Write ./so_long map/map.ber");
	d = (t_data){0};
	read_map(&d, argv[1]);
	d.mlx = mlx_init();
	if (!d.mlx)
		error_game(&d, "mlx_init failed");
	d.win = mlx_new_window(d.mlx, d.w * TILE, d.h * TILE, "so_long");
	if (!d.win)
		error_game(&d, "mlx_new_window failed");
	load_textures(&d);
	draw_map(&d);
	mlx_key_hook(d.win, key_hook, &d);
	mlx_hook(d.win, 17, 0, close_game, &d);
	mlx_loop(d.mlx);
	return (0);
}
