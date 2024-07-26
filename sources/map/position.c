/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:57:50 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 00:02:38 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    handle_player_position(t_game *game, int x, int y)
{
    game->pg->pos_x = x + 0.5;
    game->pg->pos_y = y + 0.5;
    set_player_direction_ns(game, game->map[y][x]);
    set_player_direction_we(game, game->map[y][x]);
    game->map[y][x] = '0';
}

void    handle_door_position(t_game *game, int x, int y)
{
    game->door_x = x;
    game->door_y = y;
    game->map[y][x] = '1';
}

void    set_enemy_position(t_game *game, int x, int y, int index)
{
    game->enemies[index].pos_x = x + 0.5;
    game->enemies[index].pos_y = y + 0.5;
    game->enemies[index].current_texture = game->enemies[index].texture;
    game->enemies[index].last_switch_time = 0;
    game->enemies[index].death_timer = -1;
}
