/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: synoshah <synoshah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 00:00:00 by syedh             #+#    #+#             */
/*   Updated: 2026/01/07 17:34:30 by synoshah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	try_to_move(t_data *d, int nx, int ny)
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
	ft_printf("Moved %d\n", d->moves);
	draw_map(d);
	if (target == TILE_EXIT && d->c_left == 0)
		close_game(d);
}

int	key_hook(int key, t_data *d)
{
	if (key == KEY_ESC)
		close_game(d);
	else if (key == KEY_W)
		try_to_move(d, d->px, d->py - 1);
	else if (key == KEY_S)
		try_to_move(d, d->px, d->py + 1);
	else if (key == KEY_A)
		try_to_move(d, d->px - 1, d->py);
	else if (key == KEY_D)
		try_to_move(d, d->px + 1, d->py);
	return (0);
}
