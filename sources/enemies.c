/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 23:15:30 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 12:43:57 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void update_enemy_textures(t_game *game)
{
    int switch_interval = 20;
    double enemy_speed = 0.015;
    double attack_distance = 0.7;
    double min_distance_between_enemies = 1.0;
    int attack_damage = 10; // Danno inflitto dal nemico per attacco

    for (int i = 0; i < game->num_enemies; i++)
    {
        t_enemy *enemy = &game->enemies[i];

        if (enemy->death_timer > 0)
        {
            enemy->death_timer--;
            if (enemy->death_timer == 0)
            {
                // Rimuovi il nemico dalla lista
                game->enemies[i] = game->enemies[game->num_enemies - 1];
                game->num_enemies--;
                i--; // Aggiorna l'indice per evitare di saltare il controllo del prossimo nemico
                continue;
            }
        }
        else if (enemy->death_timer == -1) // Solo i nemici vivi si muovono e attaccano
        {
            // Cambia la texture del nemico
            if (game->frame_count % switch_interval == 0)
            {
                if (enemy->current_texture == enemy->texture)
                    enemy->current_texture = enemy->texture2;
                else
                    enemy->current_texture = enemy->texture;
            }
            
            // Calcola la direzione verso il giocatore
            double dir_x = game->pg->pos_x - enemy->pos_x;
            double dir_y = game->pg->pos_y - enemy->pos_y;
            double distance = sqrt(dir_x * dir_x + dir_y * dir_y);
            dir_x /= distance;
            dir_y /= distance;

            // Controlla se il nemico può vedere il giocatore
            int visible = is_visible(game, enemy->pos_x, enemy->pos_y, game->pg->pos_x, game->pg->pos_y);

            // Logica di movimento e attacco
            if (visible && !enemy->retreating)
            {
                if (distance < attack_distance)
                {
                    enemy->current_texture = enemy->attack_texture;
                    // Il nemico attacca il giocatore
                    if (game->frame_count % switch_interval == 0) // Attacco ogni switch_interval frame
                    {
                        game->pg->health -= attack_damage;
                        if (game->pg->health <= 0)
                        {
                            printf("Game Over\n");
                            exit(0); // Termina il gioco se la salute del giocatore è zero o meno
                        }
                    }
                }
                else
                {
                    enemy->pos_x += dir_x * enemy_speed;
                    enemy->pos_y += dir_y * enemy_speed;
                    if (enemy->current_texture == enemy->attack_texture)
                    {
                        enemy->current_texture = enemy->texture;
                    }
                }
            }
            else if (enemy->retreating)
            {
                if (enemy->retreat_timer > 0)
                {
                    enemy->retreat_timer--;
                    enemy->pos_x -= dir_x * enemy_speed * 1.5;
                    enemy->pos_y -= dir_y * enemy_speed * 1.5;
                }
                else
                {
                    enemy->retreating = 0;
                }
            }

            // Mantieni distanza minima tra i nemici
            for (int j = 0; j < game->num_enemies; j++)
            {
                if (i != j && game->enemies[j].death_timer == -1)
                {
                    double dist_x = enemy->pos_x - game->enemies[j].pos_x;
                    double dist_y = enemy->pos_y - game->enemies[j].pos_y;
                    double dist_between_enemies = sqrt(dist_x * dist_x + dist_y * dist_y);
                    if (dist_between_enemies < min_distance_between_enemies)
                    {
                        double overlap = min_distance_between_enemies - dist_between_enemies;
                        enemy->pos_x += (dist_x / dist_between_enemies) * (overlap / 2);
                        enemy->pos_y += (dist_y / dist_between_enemies) * (overlap / 2);
                        game->enemies[j].pos_x -= (dist_x / dist_between_enemies) * (overlap / 2);
                        game->enemies[j].pos_y -= (dist_y / dist_between_enemies) * (overlap / 2);
                    }
                }
            }
        }
    }
}

void render_sprite(t_game *game, t_enemy *enemy)
{
    double sprite_x = enemy->pos_x - game->pg->pos_x;
    double sprite_y = enemy->pos_y - game->pg->pos_y;

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
        int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * enemy->current_texture->w / sprite_width) / 256;
        if (transform_y > 0 && stripe > 0 && stripe < WIDTH && transform_y < game->z_buffer[stripe])
        {
            for (int y = draw_start_y; y < draw_end_y; y++)
            {
                int d = (y) * 256 - HEIGHT * 128 + sprite_height * 128;
                int tex_y = ((d * enemy->current_texture->h) / sprite_height) / 256;
                int color = get_tex_color(enemy->current_texture, tex_x, tex_y);
                if (color != (0xFF << 24))
                    pixel_put(game, stripe, y, color);
            }
        }
    }
}

int is_visible(t_game *game, double x0, double y0, double x1, double y1)
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
