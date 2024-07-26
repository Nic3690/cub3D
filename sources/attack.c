/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:37:36 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/25 19:41:42 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void start_attack(t_game *game)
{
    if (game->pg->attack_cooldown == 0)
    {
        game->pg->attack = 1;
        game->pg->attack_time = 5;
        game->pg->attack_cooldown = 10;
    }
}

void update_attack_status(t_game *game)
{
    if (game->pg->attack)
    {
        if (game->pg->attack_time > 0)
            game->pg->attack_time--;
        else
        {
            game->pg->attack = 0;
            game->pg->attack_cooldown = 5;
        }
    }
    else
    {
        if (game->pg->attack_cooldown > 0)
            game->pg->attack_cooldown--;
    }
}

void attack_enemy(t_game *game, t_enemy *enemy, int attack_damage, double attack_distance)
{
    double  dir_x;
    double  dir_y;
    double  distance;

    dir_x = enemy->pos_x - game->pg->pos_x;
    dir_y = enemy->pos_y - game->pg->pos_y;
    distance = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (distance < attack_distance && game->pg->attack_time >= 5)
    {
        enemy->enemy_health -= attack_damage;
        if (enemy->enemy_health <= 0 && enemy->death_timer == -1)
        {
            enemy->current_texture = enemy->dead_texture;
            enemy->death_timer = 300;
        }
    }
}

void attack_cat(t_game *game, int attack_damage, double attack_distance)
{
    double  dir_x;
    double  dir_y;
    double  distance;

    dir_x = game->cat->pos_x - game->pg->pos_x;
    dir_y = game->cat->pos_y - game->pg->pos_y;
    distance = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (distance < attack_distance && game->pg->attack_time >= 5)
    {
        game->cat->health -= attack_damage;
        if (game->cat->health <= 0 && game->cat->death_timer == -1)
        {
            game->cat->current_texture = game->cat->dead_texture;
            game->cat->death_timer = 300;
            draw_win_lose(game, game->tex->you_win);
        }
    }
}

void player_attack(t_game *game)
{
    int     attack_damage;
    double  attack_distance;
    int     i;

    attack_damage = 10;
    attack_distance = 0.7;
    i = 0;
    while (i < game->num_enemies)
    {
        attack_enemy(game, &game->enemies[i], attack_damage, attack_distance);
        i++;
    }
    attack_cat(game, attack_damage, attack_distance);
}
