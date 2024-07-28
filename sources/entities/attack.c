/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:37:36 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 12:55:59 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    start_attack(t_game *game)
{
    if (game->pg->attack_cooldown == 0)
    {
        game->pg->attack = 1;
        game->pg->attack_time = 5;
        game->pg->attack_cooldown = 10;
    }
}

void    update_attack_status(t_game *game)
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

void    attack_enemy(t_game *g, t_enemy *e, int a_damage, double a_distance)
{
    double  dir_x;
    double  dir_y;
    double  distance;

    dir_x = e->pos_x - g->pg->pos_x;
    dir_y = e->pos_y - g->pg->pos_y;
    distance = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (distance < a_distance && g->pg->attack_time >= 5)
    {
        e->enemy_health -= a_damage;
        e->retreating = 1;
        if (e->enemy_health <= 0 && e->death_timer == -1)
        {
            e->current_texture = e->dead_texture;
            e->death_timer = 300;
        }
    }
}

void    attack_cat(t_game *game, int a_damage, double a_distance)
{
    double  dir_x;
    double  dir_y;
    double  distance;

    dir_x = game->cat->pos_x - game->pg->pos_x;
    dir_y = game->cat->pos_y - game->pg->pos_y;
    distance = sqrt(dir_x * dir_x + dir_y * dir_y);
    if (distance < a_distance && game->pg->attack_time >= 5)
    {
        game->cat->health -= a_damage;
        if (game->cat->health <= 0 && game->cat->death_timer == -1)
        {
            game->cat->current_texture = game->cat->dead_texture;
            game->cat->death_timer = 300;
            game->win_status = 1;
        }
    }
}

void    set_death_cat_texture(t_game *game)
{
    int frame_interval = 60;
    
    if (game->cat->current_texture != game->cat->dead_texture_4)
    {
        if (game->frame_count % frame_interval == 0)
            game->cat->current_texture = game->cat->dead_texture;
        else if (game->frame_count % frame_interval == frame_interval / 4)
            game->cat->current_texture = game->cat->dead_texture_2;
        else if (game->frame_count % frame_interval ==  frame_interval / 2)
            game->cat->current_texture = game->cat->dead_texture_3;
        else if (game->frame_count % frame_interval == 3 * frame_interval / 4)
            game->cat->current_texture = game->cat->dead_texture_4;
    }
}

void    player_attack(t_game *game)
{
    int     a_damage;
    double  a_distance;
    int     i;

    a_damage = 10;
    a_distance = 0.7;
    i = 0;
    while (i < game->num_enemies && game->win_status == 0)
    {
        attack_enemy(game, &game->enemies[i], a_damage, a_distance);
        i++;
    }
    attack_cat(game, a_damage, a_distance);
}
