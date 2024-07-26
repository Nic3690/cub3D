/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:41:46 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/26 18:25:53 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void update_food_textures(t_game *game)
{
    int     i;
    t_food  *f;

    i = 0;
    f = NULL;
    while (i < game->num_food)
    {
        f = &game->food[i];
        f->dir_x = game->pg->pos_x - f->pos_x;
        f->dir_y = game->pg->pos_y - f->pos_y;
        f->dist = sqrt(f->dir_x * f->dir_x + f->dir_y * f->dir_y);
        f->dir_x /= f->dist;
        f->dir_y /= f->dist;
        i++;
    }
}

void remove_food(t_game *game, int index)
{
    if (index < 0 || index >= game->num_food)
        return ;
    game->food[index].active = 0;
}

void check_food_collision(t_game *game)
{
    int     i;
    t_food  *f;

    i = 0;
    f = NULL;
    while (i < game->num_food)
    {
        f = &game->food[i];
        if (!f->active)
            continue;
        f->dist_x = game->pg->pos_x - f->pos_x;
        f->dist_y = game->pg->pos_y - f->pos_y;
        f->dist = sqrt(f->dist_x * f->dist_x + f->dist_y * f->dist_y);
        if (f->dist < FOOD_COLLISION_RADIUS)
        {
            game->pg->health += 10;
            if (game->pg->health > 100)
                game->pg->health = 100;
            remove_food(game, i);
        }
        i++;
    }
}
