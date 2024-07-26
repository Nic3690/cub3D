/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:43:57 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/23 14:24:58 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_wall(t_game *game, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;

    if (map_x >= 0 && map_x < game->map_cols && map_y >= 0 && map_y < game->map_rows)
        return game->map[map_y][map_x] == '1';
    return 0;
}

int is_near_wall(t_game *game, double x, double y, double margin)
{
    int offset_x;
    int offset_y;
    double check_x;
    double check_y;

    offset_x = -1;
    offset_y = -1;
    check_x = 0;
    check_y = 0;
    while (offset_x <= 1)
    {
        offset_y = -1;
        while (offset_y <= 1)
        {
            check_x = x + offset_x * margin;
            check_y = y + offset_y * margin;

            if (is_wall(game, check_x, check_y))
                return 1;
            offset_y++;
        }
        offset_x++;
    }
    return 0;
}

void handle_cat_collision(t_game *game)
{
    t_cat *cat = game->cat;
    double margin = 0.5;

    double next_x = cat->pos_x + cat->dir_x * cat->move_speed;
    double next_y = cat->pos_y + cat->dir_y * cat->move_speed;

    if (!is_near_wall(game, next_x, cat->pos_y, margin))
        cat->pos_x = next_x;
    if (!is_near_wall(game, cat->pos_x, next_y, margin))
        cat->pos_y = next_y;
}
