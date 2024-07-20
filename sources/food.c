/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:41:46 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 18:46:36 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

#define FOOD_COLLISION_RADIUS 0.5

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
