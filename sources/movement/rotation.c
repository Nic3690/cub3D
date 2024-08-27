/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:06:54 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:35:07 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_right(t_player *pg)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pg->dir_x;
	old_plane_x = pg->plane_x;
	pg->dir_x = pg->dir_x * cos(ROTATION_SPEED)
		- pg->dir_y * sin(ROTATION_SPEED);
	pg->dir_y = old_dir_x * sin(ROTATION_SPEED)
		+ pg->dir_y * cos(ROTATION_SPEED);
	pg->plane_x = pg->plane_x * cos(ROTATION_SPEED)
		- pg->plane_y * sin(ROTATION_SPEED);
	pg->plane_y = old_plane_x * sin(ROTATION_SPEED)
		+ pg->plane_y * cos(ROTATION_SPEED);
}

void	rotate_left(t_player *pg)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pg->dir_x;
	old_plane_x = pg->plane_x;
	pg->dir_x = pg->dir_x * cos(-ROTATION_SPEED)
		- pg->dir_y * sin(-ROTATION_SPEED);
	pg->dir_y = old_dir_x * sin(-ROTATION_SPEED)
		+ pg->dir_y * cos(-ROTATION_SPEED);
	pg->plane_x = pg->plane_x * cos(-ROTATION_SPEED)
		- pg->plane_y * sin(-ROTATION_SPEED);
	pg->plane_y = old_plane_x * sin(-ROTATION_SPEED)
		+ pg->plane_y * cos(-ROTATION_SPEED);
}
