/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_properties.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:54:02 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 15:47:20 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    set_fly_properties(t_game *game, int index)
{
    game->enemies[index].texture = game->tex->fly;
    game->enemies[index].texture2 = game->tex->fly_open;
    game->enemies[index].attack_texture = game->tex->fly_attack;
    game->enemies[index].dead_texture = game->tex->fly_dead;
    game->enemies[index].enemy_health = 100;
    game->enemies[index].speed = 0.010;
    game->enemies[index].frame = 15;
    game->enemies[index].damage = 5;
    game->enemies[index].retreat_timer = 100;
    game->enemies[index].type = FLY;
}

void    set_spider_properties(t_game *game, int index)
{
    game->enemies[index].texture = game->tex->spider;
    game->enemies[index].texture2 = game->tex->spider_2;
    game->enemies[index].attack_texture = game->tex->spider_attack;
    game->enemies[index].dead_texture = game->tex->spider_dead;
    game->enemies[index].enemy_health = 60;
    game->enemies[index].speed = 0.040;
    game->enemies[index].frame = 5;
    game->enemies[index].damage = 2;
    game->enemies[index].retreat_timer = 100;
    game->enemies[index].type = SPIDER;
}

void    set_crow_properties(t_game *game, int index)
{
    game->enemies[index].texture = game->tex->crow;
    game->enemies[index].texture2 = game->tex->crow_open;
    game->enemies[index].attack_texture = game->tex->crow_attack;
    game->enemies[index].dead_texture = game->tex->crow_dead;
    game->enemies[index].enemy_health = 80;
    game->enemies[index].speed = 0.015;
    game->enemies[index].frame = 20;
    game->enemies[index].damage = 8;
    game->enemies[index].retreat_timer = 100;
    game->enemies[index].type = CROW;
}

// modified function
void    set_cat_properties(t_game *game, int x, int y)
{
    game->cat->pos_x = x + 0.5;
    game->cat->pos_y = y + 0.5;
    game->cat->map_x = x;
    game->cat->map_y = y;
    game->cat->escape_texture = game->tex->cat_escape;
    game->cat->current_texture = game->cat->escape_texture;
    game->cat->escape_texture_2 = game->tex->cat_escape_2;
    game->cat->escape_texture_3 = game->tex->cat_escape_3;
    game->cat->escape_texture_4 = game->tex->cat_escape_4;
    game->cat->escape_texture_5 = game->tex->cat_escape_5;
    game->cat->escape_texture_6 = game->tex->cat_escape_6;
    game->cat->dead_texture = game->tex->cat_dead;
    game->cat->dead_texture_2 = game->tex->cat_dead_2;
    game->cat->dead_texture_3 = game->tex->cat_dead_3;
    game->cat->dead_texture_4 = game->tex->cat_dead_4;
    game->cat->health = 500;
    game->cat->death_timer = -1;
    game->cat->visible = 0;
    game->cat->wait_timer = 5;
    game->cat->move_speed = 0.1;
    game->cat->path = malloc(sizeof(t_coord) * (MAX_PATH_LENGTH + 1));
    game->cat->path_length = 0;
    game->cat->current_target = 0;
    game->map[y][x] = '0';
    game->is_cat = 1;
}
