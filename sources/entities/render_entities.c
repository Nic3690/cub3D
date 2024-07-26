/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:36:48 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/26 18:02:34 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void calculate_sprite_transform(t_game *g, t_entity *e)
{
    double inv_det;

    e->sprite_x = e->pos_x - g->pg->pos_x;
    e->sprite_y = e->pos_y - g->pg->pos_y;
    inv_det = 1.0 / (g->pg->plane_x * g->pg->dir_y - g->pg->dir_x * g->pg->plane_y);
    e->transform_x = inv_det * (g->pg->dir_y * e->sprite_x - g->pg->dir_x * e->sprite_y);
    e->transform_y = inv_det * (-g->pg->plane_y * e->sprite_x + g->pg->plane_x * e->sprite_y);
}

void calculate_sprite_dimensions(t_entity *e, int *screen_x)
{
    *screen_x = (int)((WIDTH / 2) * (1 + e->transform_x / e->transform_y));
    e->e_height = abs((int)(HEIGHT / e->transform_y));
    e->e_width = abs((int)(HEIGHT / e->transform_y));
}

void calculate_draw_limits(t_entity *e, int screen_x)
{
    e->draw_start_y = -e->e_height / 2 + HEIGHT / 2;
    if (e->draw_start_y < 0)
        e->draw_start_y = 0;
    e->draw_end_y = e->e_height / 2 + HEIGHT / 2;
    if (e->draw_end_y >= HEIGHT)
        e->draw_end_y = HEIGHT - 1;
    e->draw_start_x = -e->e_width / 2 + screen_x;
    if (e->draw_start_x < 0)
        e->draw_start_x = 0;
    e->draw_end_x = e->e_width / 2 + screen_x;
    if (e->draw_end_x >= WIDTH)
        e->draw_end_x = WIDTH - 1;
}

void render_entity(t_game *game, t_entity *entity)
{
    int screen_x;

    calculate_sprite_transform(game, entity);
    calculate_sprite_dimensions(entity, &screen_x);
    calculate_draw_limits(entity, screen_x);
    draw_sprite(game, entity, screen_x);
}
