/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:41:45 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/19 18:46:01 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_enemy_at(t_game *game, double x, double y)
{
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].death_timer == -1 && fabs(x - game->enemies[i].pos_x) < 0.5 && fabs(y - game->enemies[i].pos_y) < 0.5)
            return 1;
    }
    return 0;
}

void move_forward(t_game *game)
{
    double new_x = game->pg->pos_x + game->pg->dir_x * game->pg->move_speed;
    double new_y = game->pg->pos_y + game->pg->dir_y * game->pg->move_speed;

    if (game->map[(int)new_y][(int)game->pg->pos_x] == '0' && !is_enemy_at(game, game->pg->pos_x, new_y))
        game->pg->pos_y = new_y;
    if (game->map[(int)game->pg->pos_y][(int)new_x] == '0' && !is_enemy_at(game, new_x, game->pg->pos_y))
        game->pg->pos_x = new_x;
}

void move_backward(t_game *game)
{
    double new_x = game->pg->pos_x - game->pg->dir_x * game->pg->move_speed;
    double new_y = game->pg->pos_y - game->pg->dir_y * game->pg->move_speed;

    if (game->map[(int)new_y][(int)game->pg->pos_x] == '0' && !is_enemy_at(game, game->pg->pos_x, new_y))
        game->pg->pos_y = new_y;
    if (game->map[(int)game->pg->pos_y][(int)new_x] == '0' && !is_enemy_at(game, new_x, game->pg->pos_y))
        game->pg->pos_x = new_x;
}

void move_left(t_game *game)
{
    double new_x = game->pg->pos_x - game->pg->plane_x * game->pg->move_speed;
    double new_y = game->pg->pos_y - game->pg->plane_y * game->pg->move_speed;

    if (game->map[(int)new_y][(int)game->pg->pos_x] == '0' && !is_enemy_at(game, game->pg->pos_x, new_y))
        game->pg->pos_y = new_y;
    if (game->map[(int)game->pg->pos_y][(int)new_x] == '0' && !is_enemy_at(game, new_x, game->pg->pos_y))
        game->pg->pos_x = new_x;
}

void move_right(t_game *game)
{
    double new_x = game->pg->pos_x + game->pg->plane_x * game->pg->move_speed;
    double new_y = game->pg->pos_y + game->pg->plane_y * game->pg->move_speed;

    if (game->map[(int)new_y][(int)game->pg->pos_x] == '0' && !is_enemy_at(game, game->pg->pos_x, new_y))
        game->pg->pos_y = new_y;
    if (game->map[(int)game->pg->pos_y][(int)new_x] == '0' && !is_enemy_at(game, new_x, game->pg->pos_y))
        game->pg->pos_x = new_x;
}
