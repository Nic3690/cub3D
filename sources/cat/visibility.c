/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:39:57 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/23 13:39:58 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_ray(t_cat *cat, double x0, double y0, double x1, double y1)
{
    cat->ray_dir_x = x1 - x0;
    cat->ray_dir_y = y1 - y0;
    cat->distance = sqrt(cat->ray_dir_x * cat->ray_dir_x + cat->ray_dir_y * cat->ray_dir_y);
    cat->ray_dir_x /= cat->distance;
    cat->ray_dir_y /= cat->distance;

    cat->delta_x = fabs(1 / cat->ray_dir_x);
    cat->delta_y = fabs(1 / cat->ray_dir_y);
}

void calculate_step_and_side_dist(t_cat *cat, double x0, double y0, int map_x, int map_y)
{
    if (cat->ray_dir_x < 0)
    {
        cat->step_x = -1;
        cat->side_dist_x = (x0 - map_x) * cat->delta_x;
    }
    else
    {
        cat->step_x = 1;
        cat->side_dist_x = (map_x + 1.0 - x0) * cat->delta_x;
    }

    if (cat->ray_dir_y < 0)
    {
        cat->step_y = -1;
        cat->side_dist_y = (y0 - map_y) * cat->delta_y;
    }
    else
    {
        cat->step_y = 1;
        cat->side_dist_y = (map_y + 1.0 - y0) * cat->delta_y;
    }
}

int perform_dda(t_game *game, t_cat *cat, int map_x, int map_y, double x1, double y1)
{
    while (map_x != (int)x1 || map_y != (int)y1)
    {
        if (cat->side_dist_x < cat->side_dist_y)
        {
            cat->side_dist_x += cat->delta_x;
            map_x += cat->step_x;
        }
        else
        {
            cat->side_dist_y += cat->delta_y;
            map_y += cat->step_y;
        }

        if (game->map[map_y][map_x] == '1')
        {
            return 0;
        }
    }
    return 1;
}

int is_visible_cat(t_game *game, double x0, double y0, double x1, double y1)
{
    t_cat *cat = game->cat;
    int map_x = (int)x0;
    int map_y = (int)y0;

    init_ray(cat, x0, y0, x1, y1);
    calculate_step_and_side_dist(cat, x0, y0, map_x, map_y);
    return perform_dda(game, cat, map_x, map_y, x1, y1);
}
