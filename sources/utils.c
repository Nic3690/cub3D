/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:41:50 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/25 19:41:58 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_win_lose(t_game *game, t_image *texture)
{
    int x, y;
    int img_x, img_y;
    int scale = 10;

    int screen_x_start = (WIDTH - (texture->w * scale)) / 2;
    int screen_y_start = (HEIGHT - (texture->h * scale)) / 2;
    for (y = 0; y < texture->h * scale; y++)
    {
        for (x = 0; x < texture->w * scale; x++)
        {
            img_x = x / scale;
            img_y = y / scale;
            int color = get_tex_color(texture, img_x, img_y);
            if (color != (0xFF << 24))
                pixel_put(game, screen_x_start + x, screen_y_start + y, color);
        }
    }
}