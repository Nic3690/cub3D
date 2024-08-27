/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:45:03 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:13:16 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_face(t_game *game)
{
	t_image	*current;

	current = get_current_face_texture(game);
	draw_scaled_face(game, current);
}

t_image	*get_current_face_texture(t_game *game)
{
	if (game->face_state == 1)
		return (game->tex->maya_left);
	else if (game->face_state == 2)
		return (game->tex->maya_right);
	else if (game->face_state == 3)
		return (game->tex->angry_maya);
	else
		return (game->tex->maya);
}

void	draw_scaled_face(t_game *game, t_image *current)
{
	int	x;
	int	y;
	int	scale;
	int	color;

	x = 0;
	y = 0;
	scale = 3;
	color = 0;
	while (y < current->h * scale)
	{
		x = 0;
		while (x < current->w * scale)
		{
			color = get_tex_color(current, x / scale, y / scale);
			if (color != (0xFF << 24))
				pixel_put(game, WIDTH / 100 + x, HEIGHT / 75 + y, color);
			x++;
		}
		y++;
	}
}

void	update_face_state(t_game *game)
{
	if (game->pg->health <= 30)
	{
		game->face_state = 3;
		return ;
	}
	if (game->face_timer > 0)
		game->face_timer--;
	else
		cycle_face_state(game);
}

void	cycle_face_state(t_game *game)
{
	if (game->face_state == 0)
	{
		game->face_state = 1;
		game->face_timer = 60;
	}
	else if (game->face_state == 1)
	{
		game->face_state = 2;
		game->face_timer = 60;
	}
	else
	{
		game->face_state = 0;
		game->face_timer = 200;
	}
}
