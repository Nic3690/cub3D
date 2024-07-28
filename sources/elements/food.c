/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   food.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:41:46 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 15:46:04 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_food_collision(t_game *game)
{
	t_food  *f;
    int     i;

    i = 0;
    while (i < game->num_food)
    {
		f = &game->food[i];
        if (f->active)
        {
            f->dist_x = game->pg->pos_x - f->pos_x;
            f->dist_y = game->pg->pos_y - f->pos_y;
            f->dist = sqrt(f->dist_x * f->dist_x + f->dist_y * f->dist_y);
			f->dist_x /= f->dist;
            f->dist_y /= f->dist;
            if (f->dist < FOOD_COLLISION_RADIUS)
            {
                if (game->food[i].type == 0)
                    game->pg->health += 10;
                else
                    game->pg->health += 5;
                if (game->pg->health > 100)
                    game->pg->health = 100;
				game->food[i].active = 0;
            }
        }
        i++;
    }
}
