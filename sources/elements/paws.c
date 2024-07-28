/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paws.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:21:04 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:04:41 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_paws_image(t_game *game, t_image *attack_paws, int scale)
{
	int x;
	int y;
	int screen_x_start;
	int screen_y_start;
	int color;

	screen_x_start = (WIDTH - attack_paws->w * scale) / 2;
	screen_y_start = HEIGHT - attack_paws->h * scale;
	y = 0;
	while (y < attack_paws->h * scale)
	{
		x = 0;
		while (x < attack_paws->w * scale)
		{
			color = get_tex_color(attack_paws, x / scale, y / scale);
			if (color != (0xFF << 24))
				pixel_put(game, screen_x_start + x, screen_y_start + y, color);
			x++;
		}
		y++;
	}
}

void    draw_paws_attack(t_game *game)
{
	t_image *attack_paws;

	update_attack_status(game);
	if (game->pg->attack)
		attack_paws = game->tex->blood_paws;
	else
		attack_paws = game->tex->paws;
	draw_paws_image(game, attack_paws, 10);
}
