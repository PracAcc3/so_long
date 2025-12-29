/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syedh <syedh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2025/12/27 00:00:00 by syedh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	print_moves(int moves)
{
	ft_printf("Moves %d\n", moves);
}

static void	try_move(t_data *d, int nx, int ny)
{
	char	target;

	if (nx < 0 || ny < 0 || nx >= d->w || ny >= d->h)
		return ;
	target = d->map[ny][nx];
	if (target == TILE_WALL)
		return ;
	if (target == TILE_EXIT && d->c_left != 0)
		return ;
	if (target == TILE_COLLECT)
		d->c_left--;
	d->map[d->py][d->px] = TILE_FLOOR;
	d->px = nx;
	d->py = ny;
	d->map[d->py][d->px] = TILE_PLAYER;
	d->moves++;
	print_moves(d->moves);
	draw_map(d);
	if (target == TILE_EXIT && d->c_left == 0)
		close_game(d);
}

int	key_hook(int key, t_data *d)
{
	if (key == KEY_ESC)
		close_game(d);
	else if (key == KEY_W || key == KEY_UP)
		try_move(d, d->px, d->py - 1);
	else if (key == KEY_S || key == KEY_DOWN)
		try_move(d, d->px, d->py + 1);
	else if (key == KEY_A || key == KEY_LEFT)
		try_move(d, d->px - 1, d->py);
	else if (key == KEY_D || key == KEY_RIGHT)
		try_move(d, d->px + 1, d->py);
	return (0);
}
