/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:41:07 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/23 13:41:11 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_face_cat(t_game *game)
{
    int x, y;
    int img_x, img_y;
    int scale = 5;

    int screen_x_start = WIDTH - (WIDTH / 100) - 250;
    int screen_y_start = HEIGHT / 75;
    for (y = 0; y < game->tex->cat_face->h * scale; y++)
    {
        for (x = 0; x < game->tex->cat_face->w * scale; x++)
        {
            img_x = x / scale;
            img_y = y / scale;
            int color = get_tex_color(game->tex->cat_face, img_x, img_y);
            if (color != (0xFF << 24))
                pixel_put(game, screen_x_start + x, screen_y_start + y, color);
        }
    }
}
