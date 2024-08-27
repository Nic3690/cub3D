/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:19:25 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 16:24:21 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_game *g)
{
	if (keycode == 119 && g->win_status == 0)
		move_forward(g);
	if (keycode == 97 && g->win_status == 0)
		move_left(g);
	if (keycode == 115 && g->win_status == 0)
		move_backward(g);
	if (keycode == 100 && g->win_status == 0)
		move_right(g);
	if (keycode == 65361 && g->win_status == 0)
		rotate_left(g->pg);
	if (keycode == 65363 && g->win_status == 0)
		rotate_right(g->pg);
	if ((keycode == 65516 || keycode == 259) && g->win_status == 0)
	{
		start_attack(g);
		player_attack(g);
	}
	if (keycode == 32)
		open_close_door(g);
	if (keycode == 109)
		g->show_minimap = !g->show_minimap;
	if (keycode == 65307)
		exit_game(g);
	return (0);
}

int	mouse_move(int x, int y, t_game *g)
{
	static int	prev_x;
	int			delta_x;

	(void)y;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0);
	delta_x = x - prev_x;
	prev_x = x;
	if (delta_x != 0)
	{
		if (delta_x > 0)
			rotate_right(g->pg);
		else
			rotate_left(g->pg);
	}
	return (0);
}
