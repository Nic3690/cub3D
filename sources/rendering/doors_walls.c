/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:50:52 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 10:26:39 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    render_wall_column(t_game *g, int x, int side)
{
    t_image	*image;
    double	tex_pos;

    image = select_wall_texture(g, side);
    check_door_texture(g, &image);    
    g->tex->tex_w = image->w;
    g->tex->tex_h = image->h;
    g->draw->tex_x = (int)(g->draw->wall_x * (double)g->tex->tex_w);
    if (side == 0 && g->pg->ray_x > 0)
        g->draw->tex_x = g->tex->tex_w - g->draw->tex_x - 1;
    if (side == 1 && g->pg->ray_y < 0)
        g->draw->tex_x = g->tex->tex_w - g->draw->tex_x - 1;
    g->draw->step = 1.0 * g->tex->tex_w / g->draw->line;
    tex_pos = (g->draw->draw_start - HEIGHT
        / 2 + g->draw->line / 2) * g->draw->step;
    drawing(g, image, tex_pos, x);
}

t_image *select_wall_texture(t_game *g, int side)
{
    if (g->pg->map_x == g->door_x && g->pg->map_y == g->door_y)
        return (g->tex->door_light);
    if (side == 0 && g->pg->ray_x > 0)
        return (g->tex->east);
    else if (side == 0 && g->pg->ray_x < 0)
        return (g->tex->west);
    else if (side == 1 && g->pg->ray_y > 0)
        return (g->tex->south);
    else
        return (g->tex->north);
}

void    check_door_texture(t_game *g, t_image **image)
{
    int	i;

    i = 0;
    while (i < g->num_doors)
    {
        if (g->pg->map_x == g->doors[i].pos_x
            && g->pg->map_y == g->doors[i].pos_y)
        {
            *image = g->doors[i].curr_tex;
            break ;
        }
        i++;
    }
}

void    render_doors(t_game *g)
{
    int	x;

    x = 0;
    while (x < WIDTH)
    {
        calculate_ray_direction(g, x);
        identify_cell(g->pg);
        calculate_wall_distance(g, 9);
        drawing_colums(g, x);
        if (!is_door_open(g, g->pg->map_x, g->pg->map_y))
            g->z_buffer[x] = g->pg->wall_dist;
        x++;
    }
}
