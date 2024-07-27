/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:19:25 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 19:28:54 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_press(int keycode, t_game *g)
{
	if (keycode == 13 && g->win_status == 0) // W
		move_forward(g);
	if (keycode == 0 && g->win_status == 0) // A
		move_left(g);
	if (keycode == 1 && g->win_status == 0) // S
		move_backward(g);
	if (keycode == 2 && g->win_status == 0) // D
		move_right(g);
	if (keycode == 123 && g->win_status == 0) // LEFT
		rotate_left(g->pg);
	if (keycode == 124 && g->win_status == 0) // RIGHT
		rotate_right(g->pg);
	if ((keycode == 260 || keycode == 259) && g->win_status == 0)
	{
		start_attack(g); // CMD
		player_attack(g);
	}
	if (keycode == 49) // SPACE
		open_close_door(g);
	if (keycode == 46)// M
        g->show_minimap = !g->show_minimap;
	if (keycode == 53) // ESC
		exit_game(g);
	return (0);
}
