/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:33:49 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 16:53:46 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    render_door_sprite(t_game *game)
{
    double sprite_x = game->door_x - game->pg->pos_x;
    double sprite_y = game->door_y - game->pg->pos_y;

    double inv_det = 1.0 / (game->pg->plane_x * game->pg->dir_y - game->pg->dir_x * game->pg->plane_y);

    double transform_x = inv_det * (game->pg->dir_y * sprite_x - game->pg->dir_x * sprite_y);
    double transform_y = inv_det * (-game->pg->plane_y * sprite_x + game->pg->plane_x * sprite_y);

    int sprite_screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));

    int sprite_height = abs((int)(HEIGHT / transform_y));
    int draw_start_y = -sprite_height / 2 + HEIGHT / 2;
    if (draw_start_y < 0) draw_start_y = 0;
    int draw_end_y = sprite_height / 2 + HEIGHT / 2;
    if (draw_end_y >= HEIGHT) draw_end_y = HEIGHT - 1;

    int sprite_width = abs((int)(HEIGHT / transform_y));
    int draw_start_x = -sprite_width / 2 + sprite_screen_x;
    if (draw_start_x < 0) draw_start_x = 0;
    int draw_end_x = sprite_width / 2 + sprite_screen_x;
    if (draw_end_x >= WIDTH) draw_end_x = WIDTH - 1;

    for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
    {
        int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * game->tex->door_light->w / sprite_width) / 256;
        if (transform_y > 0 && stripe > 0 && stripe < WIDTH && transform_y < game->z_buffer[stripe])
        {
            for (int y = draw_start_y; y < draw_end_y; y++)
            {
                int d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
                int tex_y = ((d * game->tex->door_light->h) / sprite_height) / 256;

                if (tex_x >= 0 && tex_x < game->tex->door_light->w && tex_y >= 0 && tex_y < game->tex->door_light->h)
                {
                    int color = get_tex_color(game->tex->door_light, tex_x, tex_y);
                    if (color != (0xFF << 24))
                        pixel_put(game, stripe, y, color);
                }
            }
        }
    }
}