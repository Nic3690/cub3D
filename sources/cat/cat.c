/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:27:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/23 13:45:06 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#include "../cub3d.h"

void move_cat(t_game *game)
{
    t_cat *cat = game->cat;
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

void calculate_cat_direction(t_cat *cat)
{
    double dir_x = cat->target_x - cat->pos_x;
    double dir_y = cat->target_y - cat->pos_y;
    double distance = sqrt(dir_x * dir_x + dir_y * dir_y);
    cat->dir_x = dir_x / distance;
    cat->dir_y = dir_y / distance;
}

void check_cat_visibility(t_game *game, t_cat *cat)
{
    int visible = is_visible_cat(game, cat->pos_x, cat->pos_y, game->pg->pos_x, game->pg->pos_y);
    if (visible)
    {
        cat->visible = 1;
        if (cat->wait_timer <= 0)
            cat->wait_timer = 100;
    }
    else
        cat->visible = 0;
}

void update_cat_texture_state(t_game *game, t_cat *cat)
{
    if (fabs(cat->dir_x - game->pg->dir_x) < 0.5 && fabs(cat->dir_y - game->pg->dir_y) < 0.5)
    {
        if (game->frame_count % cat->wait_timer == 0 && cat->death_timer == -1)
        {
            if (cat->current_texture == cat->escape_texture_3)
                cat->current_texture = cat->escape_texture_4;
            else
                cat->current_texture = cat->escape_texture_3;
        }
    }
    else
    {
        if (game->frame_count % cat->wait_timer == 0 && cat->death_timer == -1)
        {
            if (cat->current_texture == cat->escape_texture)
                cat->current_texture = cat->escape_texture_2;
            else
                cat->current_texture = cat->escape_texture;
        }
    }
}

void update_cat_textures(t_game *game)
{
    t_cat *cat = game->cat;

    calculate_cat_direction(cat);
    check_cat_visibility(game, cat);
    move_cat(game);
    update_cat_texture_state(game, cat);
}
