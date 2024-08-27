/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:33:30 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:27:46 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	calculate_tex_x(t_entity *entity, int stripe, int sprite_screen_x)
{
	return ((int)(256 * (stripe
			- (-entity->e_width / 2 + sprite_screen_x))
		* entity->tex->w / entity->e_width) / 256);
}

int	is_valid_stripe(t_game *game, t_entity *entity, int stripe)
{
	return ((entity->transform_y > 0 && stripe > 0
			&& stripe < WIDTH
			&& entity->transform_y < game->z_buffer[stripe]));
}

void	draw_sprite_column(t_game *game, t_entity *entity, int stripe)
{
	int	y;
	int	d;
	int	color;

	y = entity->draw_start_y;
	while (y < entity->draw_end_y)
	{
		d = (y) * 256 - HEIGHT * 128 + entity->e_height * 128;
		entity->tex_y = ((d * entity->tex->h) / entity->e_height) / 256;
		color = get_tex_color(entity->tex, entity->tex_x, entity->tex_y);
		if (color != (0xFF << 24))
			pixel_put(game, stripe, y, color);
		y++;
	}
}

void	draw_sprite(t_game *game, t_entity *entity, int sprite_screen_x)
{
	int	stripe;

	stripe = entity->draw_start_x;
	while (stripe < entity->draw_end_x)
	{
		entity->tex_x = calculate_tex_x(entity, stripe, sprite_screen_x);
		if (is_valid_stripe(game, entity, stripe))
			draw_sprite_column(game, entity, stripe);
		stripe++;
	}
}
