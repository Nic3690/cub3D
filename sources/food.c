/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:41:46 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 16:36:33 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define FOOD_COLLISION_RADIUS 0.5

void swap_food(t_food *a, t_food *b)
{
    t_food temp = *a;
    *a = *b;
    *b = temp;
}

int partition_food(t_food *arr, int low, int high)
{
    double pivot = arr[high].dist;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].dist > pivot)
        {
            i++;
            swap_food(&arr[i], &arr[j]);
        }
    }
    swap_food(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort_food(t_food *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition_food(arr, low, high);

        quick_sort_food(arr, low, pi - 1);
        quick_sort_food(arr, pi + 1, high);
    }
}

void calculate_food_distances(t_game *game)
{
    for (int i = 0; i < game->num_food; i++)
    {
        t_food *food = &game->food[i];
        food->dist = ((game->pg->pos_x - food->pos_x) * (game->pg->pos_x - food->pos_x) +
                       (game->pg->pos_y - food->pos_y) * (game->pg->pos_y - food->pos_y));
    }
}

void update_food_textures(t_game *game)
{
    for (int i = 0; i < game->num_food; i++)
    {
        t_food *food = &game->food[i];
            
        // Calcola la direzione verso il giocatore
        double dir_x = game->pg->pos_x - food->pos_x;
        double dir_y = game->pg->pos_y - food->pos_y;
        double distance = sqrt(dir_x * dir_x + dir_y * dir_y);
        dir_x /= distance;
        dir_y /= distance;
    }
}

void render_food_sprite(t_game *game, t_food *food)
{
    if (!food->active)
        return;
    double sprite_x = food->pos_x - game->pg->pos_x;
    double sprite_y = food->pos_y - game->pg->pos_y;

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
        int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * food->texture->w / sprite_width) / 256;
        if (transform_y > 0 && stripe > 0 && stripe < WIDTH && transform_y < game->z_buffer[stripe])
        {
            for (int y = draw_start_y; y < draw_end_y; y++)
            {
                int d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
                int tex_y = ((d * food->texture->h) / sprite_height) / 256;

                if (tex_x >= 0 && tex_x < food->texture->w && tex_y >= 0 && tex_y < food->texture->h)
                {
                    int color = get_tex_color(food->texture, tex_x, tex_y);
                    if (color != (0xFF << 24))
                        pixel_put(game, stripe, y, color);
                }
            }
        }
    }
}

void remove_food(t_game *game, int index)
{
    if (index < 0 || index >= game->num_food)
        return;

    game->food[index].active = 0;
}

void check_food_collision(t_game *game)
{
    for (int i = 0; i < game->num_food; i++)
    {
        t_food *food = &game->food[i];
        if (!food->active)
            continue; // Salta il cibo non attivo

        double dist_x = game->pg->pos_x - food->pos_x;
        double dist_y = game->pg->pos_y - food->pos_y;
        double distance = sqrt(dist_x * dist_x + dist_y * dist_y);

        if (distance < FOOD_COLLISION_RADIUS)
        {
            // Aumenta la salute del giocatore del 10%, senza superare il 100%
            game->pg->health += 10;
            if (game->pg->health > 100)
                game->pg->health = 100;

            // Disattiva il cibo
            remove_food(game, i);

            printf("Cibo raccolto! Salute aumentata al %d%%\n", game->pg->health);
        }
    }
}
