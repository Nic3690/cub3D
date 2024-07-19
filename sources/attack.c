/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:37:36 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/19 19:40:27 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void start_attack(t_game *game)
{
    if (game->pg->attack_cooldown == 0)
    {
        game->pg->attack = 1;
        game->pg->attack_time = 10;
        game->pg->attack_cooldown = 20;
    }
}

void draw_paws_attack(t_game *game)
{
    t_image *attack_paws;

    if (game->pg->attack)
    {
        if (game->pg->attack_time > 0)
            game->pg->attack_time--;
        else
        {
            game->pg->attack = 0;
            game->pg->attack_cooldown = 20; // Imposta il cooldown tra gli attacchi (in frame)
        }
        attack_paws = game->tex->blood_paws;
    }
    else
    {
        attack_paws = game->tex->paws;
        if (game->pg->attack_cooldown > 0)
            game->pg->attack_cooldown--; // Decrementa il cooldown ad ogni frame
    }

    int x, y;
    int img_x, img_y;
    int scale = 10;
    int screen_x_start = (WIDTH - attack_paws->w * scale) / 2;
    int screen_y_start = HEIGHT - attack_paws->h * scale;

    for (y = 0; y < attack_paws->h * scale; y++)
    {
        for (x = 0; x < attack_paws->w * scale; x++)
        {
            img_x = x / scale;
            img_y = y / scale;
            int color = get_tex_color(attack_paws, img_x, img_y);
            if (color != (0xFF << 24))
                pixel_put(game, screen_x_start + x, screen_y_start + y, color);
        }
    }
}

void player_attack(t_game *game)
{
    int attack_damage = 10; // Danno inflitto dal giocatore per attacco
    double attack_distance = 0.7;

    for (int i = 0; i < game->num_enemies; i++)
    {
        t_enemy *enemy = &game->enemies[i];

        double dir_x = enemy->pos_x - game->pg->pos_x;
        double dir_y = enemy->pos_y - game->pg->pos_y;
        double distance = sqrt(dir_x * dir_x + dir_y * dir_y);

        if (distance < attack_distance)
        {
            enemy->enemy_health -= attack_damage;
            if (enemy->enemy_health <= 0 && enemy->death_timer == -1)
            {
                printf("Enemy defeated!\n");
                enemy->current_texture = enemy->dead_texture;
                enemy->death_timer = 300;
            }
        }
    }
}
