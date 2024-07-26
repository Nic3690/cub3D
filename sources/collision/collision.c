/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:41:45 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/25 19:53:00 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void move_forward(t_game *game)
{
    double  new_x;
    double  new_y;

    new_x = game->pg->pos_x + game->pg->dir_x * game->pg->move_speed;
    new_y = game->pg->pos_y + game->pg->dir_y * game->pg->move_speed;
    if ((game->map[(int)new_y][(int)game->pg->pos_x] == '0'
        || is_food(game, game->pg->pos_x, new_y)
        || is_door_open(game, game->pg->pos_x, new_y))
        && !is_enemy_at(game, game->pg->pos_x, new_y))
        game->pg->pos_y = new_y;
    if ((game->map[(int)game->pg->pos_y][(int)new_x] == '0'
        || is_food(game, new_x, game->pg->pos_y)
        || is_door_open(game, new_x, game->pg->pos_y))
        && !is_enemy_at(game, new_x, game->pg->pos_y))
        game->pg->pos_x = new_x;
}

void move_backward(t_game *game)
{
    double  new_x;
    double  new_y;

    new_x = game->pg->pos_x - game->pg->dir_x * game->pg->move_speed;
    new_y = game->pg->pos_y - game->pg->dir_y * game->pg->move_speed;
    if ((game->map[(int)new_y][(int)game->pg->pos_x] == '0'
        || is_food(game, game->pg->pos_x, new_y)
        || is_door_open(game, game->pg->pos_x, new_y))
        && !is_enemy_at(game, game->pg->pos_x, new_y))
        game->pg->pos_y = new_y;
    if ((game->map[(int)game->pg->pos_y][(int)new_x] == '0'
        || is_food(game, new_x, game->pg->pos_y)
        || is_door_open(game, new_x, game->pg->pos_y))
        && !is_enemy_at(game, new_x, game->pg->pos_y))
        game->pg->pos_x = new_x;
}

void move_left(t_game *game)
{
    double  new_x;
    double  new_y;

    new_x = game->pg->pos_x - game->pg->plane_x * game->pg->move_speed;
    new_y = game->pg->pos_y - game->pg->plane_y * game->pg->move_speed;
    if ((game->map[(int)new_y][(int)game->pg->pos_x] == '0'
        || is_food(game, game->pg->pos_x, new_y)
        || is_door_open(game, game->pg->pos_x, new_y))
        && !is_enemy_at(game, game->pg->pos_x, new_y))
        game->pg->pos_y = new_y;
    if ((game->map[(int)game->pg->pos_y][(int)new_x] == '0'
        || is_food(game, new_x, game->pg->pos_y)
        || is_door_open(game, new_x, game->pg->pos_y))
        && !is_enemy_at(game, new_x, game->pg->pos_y))
        game->pg->pos_x = new_x;
}

void move_right(t_game *game)
{
    double  new_x;
    double  new_y;

    new_x = game->pg->pos_x + game->pg->plane_x * game->pg->move_speed;
    new_y = game->pg->pos_y + game->pg->plane_y * game->pg->move_speed;
    if ((game->map[(int)new_y][(int)game->pg->pos_x] == '0'
        || is_food(game, game->pg->pos_x, new_y)
        || is_door_open(game, game->pg->pos_x, new_y))
        && !is_enemy_at(game, game->pg->pos_x, new_y))
        game->pg->pos_y = new_y;
    if ((game->map[(int)game->pg->pos_y][(int)new_x] == '0'
        || is_food(game, new_x, game->pg->pos_y)
        || is_door_open(game, new_x, game->pg->pos_y))
        && !is_enemy_at(game, new_x, game->pg->pos_y))
        game->pg->pos_x = new_x;
}
