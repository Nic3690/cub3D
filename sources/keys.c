/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 21:19:25 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/13 22:06:48 by nfurlani         ###   ########.fr       */
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
	printf("keycode: %d\n", keycode);
	if (keycode == 13) // W
	{
		g->pg->pos_x += g->pg->dir_x * g->pg->move_speed;
		g->pg->pos_y += g->pg->dir_y * g->pg->move_speed;
	}
	if (keycode == 0) // A
	{
		g->pg->pos_x += g->pg->dir_y * g->pg->move_speed;
		g->pg->pos_y -= g->pg->dir_x * g->pg->move_speed;
	}
	if (keycode == 1) // S
	{
		g->pg->pos_x -= g->pg->dir_x * g->pg->move_speed;
		g->pg->pos_y -= g->pg->dir_y * g->pg->move_speed;
	}
	if (keycode == 2) // D
	{
		g->pg->pos_x -= g->pg->dir_y * g->pg->move_speed;
		g->pg->pos_y += g->pg->dir_x * g->pg->move_speed;
	}
	if (keycode == 123) // LEFT
		rotate_left(g->pg);
	if (keycode == 124) // RIGHT
		rotate_right(g->pg);
    render_ceiling_and_floor(g);
	return (0);
}
