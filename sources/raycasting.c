/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:13:41 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 16:54:06 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void calculate_ray_direction(t_game *g, int x)
{
    double camera_x = 2 * x / (double)WIDTH - 1;
    g->pg->ray_x = g->pg->dir_x + g->pg->plane_x * camera_x;
    g->pg->ray_y = g->pg->dir_y + g->pg->plane_y * camera_x;
}

void identify_cell(t_player *pg)
{
    pg->map_x = (int)pg->pos_x;
    pg->map_y = (int)pg->pos_y;

    pg->delta_x = (pg->ray_x != 0) ? fabs(1 / pg->ray_x) : DBL_MAX;
    pg->delta_y = (pg->ray_y != 0) ? fabs(1 / pg->ray_y) : DBL_MAX;

    if (pg->ray_x < 0)
    {
        pg->step_x = -1;
        pg->side_x = (pg->pos_x - pg->map_x) * pg->delta_x;
    }
    else
    {
        pg->step_x = 1;
        pg->side_x = (pg->map_x + 1.0 - pg->pos_x) * pg->delta_x;
    }
    if (pg->ray_y < 0)
    {
        pg->step_y = -1;
        pg->side_y = (pg->pos_y - pg->map_y) * pg->delta_y;
    }
    else
    {
        pg->step_y = 1;
        pg->side_y = (pg->map_y + 1.0 - pg->pos_y) * pg->delta_y;
    }
}

void calculate_wall_distance(t_game *g)
{
    int hit = 0;
	
    while (hit == 0)
    {
        if (g->pg->side_x < g->pg->side_y)
        {
            g->pg->side_x += g->pg->delta_x;
            g->pg->map_x += g->pg->step_x;
            g->pg->side = 0;
        }
        else
        {
            g->pg->side_y += g->pg->delta_y;
            g->pg->map_y += g->pg->step_y;
            g->pg->side = 1;
        }

        if (g->map[g->pg->map_y][g->pg->map_x] == '1')
            hit = 1;
    }
    calculate_wall_side(g);
}

void calculate_wall_side(t_game *g)
{
    if (g->pg->side == 0)
        g->pg->wall_dist = (g->pg->map_x - g->pg->pos_x
            + (1 - g->pg->step_x) / 2) / g->pg->ray_x;
    else
        g->pg->wall_dist = (g->pg->map_y - g->pg->pos_y
            + (1 - g->pg->step_y) / 2) / g->pg->ray_y;
}

int calculate_line_height(t_player *pg, int side)
{
    double wall_dist = (side == 0) ?
        (pg->map_x - pg->pos_x + (1 - pg->step_x) / 2) / pg->ray_x :
        (pg->map_y - pg->pos_y + (1 - pg->step_y) / 2) / pg->ray_y;
    return (int)(HEIGHT / wall_dist);
}
