/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:19:25 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/19 17:02:31 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void rotate_right(t_player *pg)
{
    double old_dir_x = pg->dir_x;
    double old_plane_x = pg->plane_x;

    pg->dir_x = pg->dir_x * cos(ROTATION_SPEED) - pg->dir_y * sin(ROTATION_SPEED);
    pg->dir_y = old_dir_x * sin(ROTATION_SPEED) + pg->dir_y * cos(ROTATION_SPEED);
    pg->plane_x = pg->plane_x * cos(ROTATION_SPEED) - pg->plane_y * sin(ROTATION_SPEED);
    pg->plane_y = old_plane_x * sin(ROTATION_SPEED) + pg->plane_y * cos(ROTATION_SPEED);
}

void rotate_left(t_player *pg)
{
    double old_dir_x = pg->dir_x;
    double old_plane_x = pg->plane_x;

    pg->dir_x = pg->dir_x * cos(-ROTATION_SPEED) - pg->dir_y * sin(-ROTATION_SPEED);
    pg->dir_y = old_dir_x * sin(-ROTATION_SPEED) + pg->dir_y * cos(-ROTATION_SPEED);
    pg->plane_x = pg->plane_x * cos(-ROTATION_SPEED) - pg->plane_y * sin(-ROTATION_SPEED);
    pg->plane_y = old_plane_x * sin(-ROTATION_SPEED) + pg->plane_y * cos(-ROTATION_SPEED);
}

int	key_press(int keycode, t_game *g)
{
	if (keycode == 13) // W
		move_forward(g);
	if (keycode == 0) // A
		move_left(g);
	if (keycode == 1) // S
		move_backward(g);
	if (keycode == 2) // D
		move_right(g);
	if (keycode == 123) // LEFT
		rotate_left(g->pg);
	if (keycode == 124) // RIGHT
		rotate_right(g->pg);
	if (keycode == 3) // F
		g->pg->health -= 10;
	if (keycode == 260 || keycode == 259)
	{
		start_attack(g); // CMD
		player_attack(g);
	}
	return (0);
}
