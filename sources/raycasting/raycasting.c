/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:13:41 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 11:24:50 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    calculate_ray_direction(t_game *g, int x)
{
    double  camera_x;

    camera_x = 2 * x / (double)WIDTH - 1;
    g->pg->ray_x = g->pg->dir_x + g->pg->plane_x * camera_x;
    g->pg->ray_y = g->pg->dir_y + g->pg->plane_y * camera_x;
}

void    identify_cell(t_player *pg)
{
    pg->map_x = (int)pg->pos_x;
    pg->map_y = (int)pg->pos_y;
    calculate_deltas(pg);
    calculate_steps(pg);
}

void    init_side(t_game *g)
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
}
