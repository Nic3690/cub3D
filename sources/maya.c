/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maya.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:45:03 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/21 12:18:19 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_face(t_game *game)
{
    int x, y;
    int img_x, img_y;
    int scale = 3;
    t_image *current;

    int screen_x_start = WIDTH / 100;
    int screen_y_start = HEIGHT / 75;

    if (game->face_state == 1)
        current = game->tex->maya_left;
    else if (game->face_state == 2)
        current = game->tex->maya_right;
    else if (game->face_state == 3)
        current = game->tex->angry_maya;
    else
        current = game->tex->maya;

    for (y = 0; y < current->h * scale; y++)
    {
        for (x = 0; x < current->w * scale; x++)
        {
            img_x = x / scale;
            img_y = y / scale;
            int color = get_tex_color(current, img_x, img_y);
            if (color != (0xFF << 24))
                pixel_put(game, screen_x_start + x, screen_y_start + y, color);
        }
    }
}

void update_face_state(t_game *game)
{
    if (game->pg->health <= 30)
    {
        game->face_state = 3;
        return;
    }
    if (game->face_timer > 0)
    {
        game->face_timer--;
    }
    else
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
}
