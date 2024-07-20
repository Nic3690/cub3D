/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:27:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 18:48:28 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void move_cat(t_game *game)
{
    t_cat *cat = game->cat;
    double dir_x = cat->target_x - cat->pos_x;
    double dir_y = cat->target_y - cat->pos_y;
    double distance = sqrt(dir_x * dir_x + dir_y * dir_y);
    double move_speed = 0.01;

    if (distance > move_speed)
    {
        dir_x /= distance;
        dir_y /= distance;
        cat->pos_x += dir_x * move_speed;
        cat->pos_y += dir_y * move_speed;
    }
}

void update_cat_textures(t_game *game)
{
    t_cat *cat = game->cat;

    // Calcola la direzione verso il punto di destinazione
    double dir_x = cat->target_x - cat->pos_x;
    double dir_y = cat->target_y - cat->pos_y;
    double distance = sqrt(dir_x * dir_x + dir_y * dir_y);
    dir_x /= distance;
    dir_y /= distance;

    // Controlla se il gatto è visibile dal giocatore
    int visible = is_visible_cat(game, cat->pos_x, cat->pos_y, game->pg->pos_x, game->pg->pos_y);

    if (visible)
    {
        cat->visible = 1;
        if (cat->wait_timer <= 0) // Inizia a contare il tempo solo quando il gatto viene visto per la prima volta
        {
            cat->wait_timer = 100; // Imposta un timer di attesa quando il gatto viene visto
        }
    }
    else
    {
        cat->visible = 0;
    }

    // Muove il gatto verso il punto di destinazione
    move_cat(game);

    // Cambia la texture del gatto in base allo stato di movimento
    if (fabs(dir_x - game->pg->dir_x) < 0.5 && fabs(dir_y - game->pg->dir_y) < 0.5)
    {
        if (game->frame_count % cat->wait_timer == 0)
        {
            if (cat->current_texture == cat->escape_texture_3)
                cat->current_texture = cat->escape_texture_4;
            else
                cat->current_texture = cat->escape_texture_3;
        }
    }
    else
    {
        if (game->frame_count % cat->wait_timer == 0)
        {
            if (cat->current_texture == cat->escape_texture)
                cat->current_texture = cat->escape_texture_2;
            else
                cat->current_texture = cat->escape_texture;
        }
    }
}

int is_visible_cat(t_game *game, double x0, double y0, double x1, double y1)
{
    int map_x, map_y;
    double delta_x, delta_y;
    double side_dist_x, side_dist_y;
    double ray_dir_x = x1 - x0;
    double ray_dir_y = y1 - y0;
    double step_x, step_y;

    double distance = sqrt(ray_dir_x * ray_dir_x + ray_dir_y * ray_dir_y);
    ray_dir_x /= distance;
    ray_dir_y /= distance;

    map_x = (int)x0;
    map_y = (int)y0;

    delta_x = fabs(1 / ray_dir_x);
    delta_y = fabs(1 / ray_dir_y);

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (x0 - map_x) * delta_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - x0) * delta_x;
    }

    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (y0 - map_y) * delta_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - y0) * delta_y;
    }

    while (map_x != (int)x1 || map_y != (int)y1)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_x;
            map_x += step_x;
        }
        else
        {
            side_dist_y += delta_y;
            map_y += step_y;
        }

        if (game->map[map_y][map_x] == '1')
        {
            return 0;
        }
    }
    return 1;
}
