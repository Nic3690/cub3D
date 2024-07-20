/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:34:39 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 18:35:02 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void calculate_entity_distances(t_game *game, t_entity *entities, int *entity_count)
{
    *entity_count = 0;

    // Aggiungi cibo
    for (int i = 0; i < game->num_food; i++)
    {
        if (game->food[i].active)
        {
            entities[*entity_count].pos_x = game->food[i].pos_x;
            entities[*entity_count].pos_y = game->food[i].pos_y;
            entities[*entity_count].texture = game->food[i].texture;
            entities[*entity_count].dist = ((game->pg->pos_x - game->food[i].pos_x) * (game->pg->pos_x - game->food[i].pos_x) +
                                            (game->pg->pos_y - game->food[i].pos_y) * (game->pg->pos_y - game->food[i].pos_y));
            (*entity_count)++;
        }
    }

    // Aggiungi nemici
    for (int i = 0; i < game->num_enemies; i++)
    {
        entities[*entity_count].pos_x = game->enemies[i].pos_x;
        entities[*entity_count].pos_y = game->enemies[i].pos_y;
        entities[*entity_count].texture = game->enemies[i].current_texture;
        entities[*entity_count].dist = ((game->pg->pos_x - game->enemies[i].pos_x) * (game->pg->pos_x - game->enemies[i].pos_x) +
                                        (game->pg->pos_y - game->enemies[i].pos_y) * (game->pg->pos_y - game->enemies[i].pos_y));
        (*entity_count)++;
    }

    // Aggiungi gatto
    entities[*entity_count].pos_x = game->cat->pos_x;
    entities[*entity_count].pos_y = game->cat->pos_y;
    entities[*entity_count].texture = game->cat->current_texture;
    entities[*entity_count].dist = ((game->pg->pos_x - game->cat->pos_x) * (game->pg->pos_x - game->cat->pos_x) +
                                    (game->pg->pos_y - game->cat->pos_y) * (game->pg->pos_y - game->cat->pos_y));
    (*entity_count)++;

    // Ordina le entità in base alla distanza
    for (int i = 0; i < *entity_count - 1; i++)
    {
        for (int j = i + 1; j < *entity_count; j++)
        {
            if (entities[i].dist < entities[j].dist)
            {
                t_entity temp = entities[i];
                entities[i] = entities[j];
                entities[j] = temp;
            }
        }
    }
}

void render_entity(t_game *game, t_entity *entity)
{
    double sprite_x = entity->pos_x - game->pg->pos_x;
    double sprite_y = entity->pos_y - game->pg->pos_y;

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
        int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * entity->texture->w / sprite_width) / 256;
        if (transform_y > 0 && stripe > 0 && stripe < WIDTH && transform_y < game->z_buffer[stripe])
        {
            for (int y = draw_start_y; y < draw_end_y; y++)
            {
                int d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
                int tex_y = ((d * entity->texture->h) / sprite_height) / 256;
                int color = get_tex_color(entity->texture, tex_x, tex_y);
                if (color != (0xFF << 24))
                    pixel_put(game, stripe, y, color);
            }
        }
    }
}