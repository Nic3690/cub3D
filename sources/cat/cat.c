/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:27:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 19:03:01 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_face_cat(t_game *game)
{
    int scale;
    int x_start;
    int y_start;

    scale = 5;
    x_start = WIDTH - (WIDTH / 100) - 250;
    y_start = HEIGHT / 75;
    draw_cat_face(game, scale, x_start, y_start);
}

void    draw_cat_face(t_game *game, int scale, int x_start, int y_start)
{
    int x;
    int y;
    int img_x;
    int img_y;
    int color;

    x = 0;
    y = 0;
    while (y < game->tex->cat_face->h * scale)
    {
        x = 0;
        while (x < game->tex->cat_face->w * scale)
        {
            img_x = x / scale;
            img_y = y / scale;
            color = get_tex_color(game->tex->cat_face, img_x, img_y);
            if (color != (0xFF << 24))
                pixel_put(game, x_start + x, y_start + y, color);
            x++;
        }
        y++;
    }
}

void    move_cat(t_game *game)
{
    t_cat   *cat;

    cat = game->cat;
    cat->dir_x = cat->target_x - cat->pos_x;
    cat->dir_y = cat->target_y - cat->pos_y;
    cat->distance = sqrt(cat->dir_x * cat->dir_x + cat->dir_y * cat->dir_y);
    cat->move_speed = 0.01;
    if (cat->distance > cat->move_speed && cat->death_timer == -1)
    {
        cat->dir_x /= cat->distance;
        cat->dir_y /= cat->distance;
        handle_cat_collision(game);
    }
}

void    check_cat_visibility(t_game *g, t_cat *cat)
{
    int visible;
    
    visible = is_visible_cat(g);
    if (visible)
    {
        cat->visible = 1;
        if (cat->wait_timer <= 0)
            cat->wait_timer = 100;
    }
    else
        cat->visible = 0;
}

void    update_cat_textures(t_game *game)
{
    t_cat   *cat;
    
    cat = game->cat;
    calculate_cat_direction(cat);
    check_cat_visibility(game, cat);
    move_cat(game);
    update_cat_texture_state(game, cat);
    if (cat->death_timer > 0)
        set_death_cat_texture(game);
}
