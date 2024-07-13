/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:11 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/13 23:56:35 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_paws(t_game *game, t_image *paws)
{
    int x, y;
    int img_x, img_y;
    int scale = 10;
    int screen_x_start = (WIDTH - paws->w * scale) / 2;
    int screen_y_start = HEIGHT - paws->h * scale;

    for (y = 0; y < paws->h * scale; y++)
    {
        for (x = 0; x < paws->w * scale; x++)
        {
            img_x = x / scale;
            img_y = y / scale;
            int color = get_tex_color(paws, img_x, img_y);
            if (color != (0xFF << 24))
                pixel_put(game, screen_x_start + x, screen_y_start + y, color);
        }
    }
}

void render_ceiling_and_floor(t_game *g)
{
    int y;
    t_image *image;
    double row_dist;

    y = 0;
    image = NULL;
    row_dist = 0;
    while (y < HEIGHT)
    {
        image = check_sky_floor(g, image, y, &row_dist);
        g->pg->ray_x0 = g->pg->dir_x - g->pg->plane_x;
        g->pg->ray_y0 = g->pg->dir_y - g->pg->plane_y;
        g->pg->ray_x1 = g->pg->dir_x + g->pg->plane_x;
        g->pg->ray_y1 = g->pg->dir_y + g->pg->plane_y;
        g->tex->step_x = row_dist * (g->pg->ray_x1 - g->pg->ray_x0) / WIDTH;
        g->tex->step_y = row_dist * (g->pg->ray_y1 - g->pg->ray_y0) / WIDTH;
        g->pg->fx = g->pg->pos_x + row_dist * g->pg->ray_x0;
        g->pg->fy = g->pg->pos_y + row_dist * g->pg->ray_y0;
        color_floor_and_sky(g, image, y);
        y++;
    }
}

t_image *check_sky_floor(t_game *g, t_image *image, int y, double *row_dist)
{
    int half;

    half = 0;
    if (y < HEIGHT / 2)
    {
        image = g->tex->sky;
        half = y;
    }
    else
    {
        image = g->tex->floor;
        half = HEIGHT - y - 1;
    }
    *row_dist = 0.5 * HEIGHT / (half - HEIGHT / 2);
    return (image);
}

void    color_floor_and_sky(t_game *g, t_image *img, int y)
{
    int x;
    
    x = -1;
    while (x++ < WIDTH)
    {
        g->tex->x = (int)(img->w * (g->pg->fx - (int)g->pg->fx))
            & (img->w - 1);
        g->tex->y = (int)(img->h * (g->pg->fy - (int)g->pg->fy))
            & (img->h - 1);
        g->pg->fx += g->tex->step_x;
        g->pg->fy += g->tex->step_y;
        pixel_put(g, x, y, get_tex_color(img, g->tex->x, g->tex->y));
    }
}

void render_wall_column(t_game *g, int x, t_draw *draw, int side)
{
    t_image *image;
	double	tex_pos;

    if (side == 0 && g->pg->ray_x > 0)
        image = g->tex->east;
    else if (side == 0 && g->pg->ray_x < 0)
        image = g->tex->west;
    else if (side == 1 && g->pg->ray_y > 0)
        image = g->tex->south;
    else
        image = g->tex->north;
    g->tex->tex_w = image->w;
    g->tex->tex_h = image->h;
    draw->tex_x = (int)(draw->wall_x * (double)g->tex->tex_w);
    if (side == 0 && g->pg->ray_x > 0)
		draw->tex_x = g->tex->tex_w - draw->tex_x - 1;
    if (side == 1 && g->pg->ray_y < 0)
		draw->tex_x = g->tex->tex_w - draw->tex_x - 1;
    draw->step = 1.0 * g->tex->tex_w / draw->line;
    tex_pos = (draw->draw_start - HEIGHT / 2 + draw->line / 2) * draw->step;
	drawing(g, image, tex_pos, x);
}

int render_game(t_game *game)
{
	int x;

	x = 0;
    game->z_buffer = malloc(sizeof(double) * WIDTH);
	while (x < WIDTH)
    {
        calculate_ray_direction(game, x);
        identify_cell(game->pg);
        calculate_wall_distance(game);
		drawing_colums(game, x);
        game->z_buffer[x] = game->pg->wall_dist;
		x++;
    }
    for (int i = 0; i < game->num_enemies; i++)
        render_sprite(game, &game->enemies[i]);
    draw_paws(game, game->tex->paws);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    free(game->z_buffer);
    return (0);
}
