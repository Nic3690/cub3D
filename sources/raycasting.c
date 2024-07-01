/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:13:41 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/01 15:29:40 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

t_image *check_sky_floor(t_game *game, t_image *image, int y, double *row_dist)
{
    int half;

    half = 0;
    if (y < HEIGHT / 2)
    {
        image = game->tex->sky;
        half = y;
    }
    else
    {
        image = game->tex->floor;
        half = HEIGHT - y - 1;
    }
    *row_dist = 0.5 * HEIGHT / (half - HEIGHT / 2);
    return (image);
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

void calculate_ray_direction(t_game *game, int x)
{
    double camera_x = 2 * x / (double)WIDTH - 1;
    game->pg->ray_x = game->pg->dir_x + game->pg->plane_x * camera_x;
    game->pg->ray_y = game->pg->dir_y + game->pg->plane_y * camera_x;
}

void identify_cell(t_player *pg)
{
    pg->map_x = (int)pg->pos_x;
    pg->map_y = (int)pg->pos_y;

    pg->delta_x = (pg->ray_x != 0) ? fabs(1 / pg->ray_x) : DBL_MAX;
    pg->delta_y = (pg->ray_y != 0) ? fabs(1 / pg->ray_y) : DBL_MAX;

    int step_x = (pg->ray_x < 0) ? -1 : 1;
    int step_y = (pg->ray_y < 0) ? -1 : 1;

    if (pg->ray_x < 0)
        pg->side_x = (pg->pos_x - pg->map_x) * pg->delta_x;
    else
        pg->side_x = (pg->map_x + 1.0 - pg->pos_x) * pg->delta_y;

    if (pg->ray_y < 0)
        pg->side_y = (pg->pos_y - pg->map_y) * pg->delta_x;
    else
        pg->side_y = (pg->map_y + 1.0 - pg->pos_y) * pg->delta_y;
    pg->step_x = step_x;
    pg->step_y = step_y;
}

void calculate_wall_distance(t_game *g)
{
    int		hit;
	
	hit = 0;
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
    if (g->pg->side == 0)
        g->pg->wall_dist = (g->pg->map_x - g->pg->pos_x + (1 - g->pg->step_x) / 2) / g->pg->ray_x;
    else
        g->pg->wall_dist = (g->pg->map_y - g->pg->pos_y + (1 - g->pg->step_y) / 2) / g->pg->ray_y;
}

int calculate_line_height(t_player *pg, int side)
{
    double wall_dist = (side == 0) ?
        (pg->map_x - pg->pos_x + (1 - pg->step_x) / 2) / pg->ray_x :
        (pg->map_y - pg->pos_y + (1 - pg->step_y) / 2) / pg->ray_y;
    return (int)(HEIGHT / wall_dist);
}

int get_tex_color(t_image *image, int tex_x, int tex_y)
{
    int *texture = (int *)image->addr;
    return texture[tex_y * image->w + tex_x];
}

void render_wall_column(t_game *game, int x, int line_height, int draw_start, int draw_end, int side, double wall_x)
{
    t_image *image;

    if (side == 0 && game->pg->ray_x > 0)
        image = game->tex->east;
    else if (side == 0 && game->pg->ray_x < 0)
        image = game->tex->west;
    else if (side == 1 && game->pg->ray_y > 0)
        image = game->tex->south;
    else
        image = game->tex->north;

    game->tex->tex_w = image->w;
    game->tex->tex_h = image->h;

    int tex_x = (int)(wall_x * (double)game->tex->tex_w);
    if (side == 0 && game->pg->ray_x > 0) tex_x = game->tex->tex_w - tex_x - 1;
    if (side == 1 && game->pg->ray_y < 0) tex_x = game->tex->tex_w - tex_x - 1;

    double step = 1.0 * game->tex->tex_w / line_height;
    double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;

    for (int y = draw_start; y < draw_end; y++)
    {
        int tex_y = (int)tex_pos & (game->tex->tex_h - 1);
        tex_pos += step;
        int color = get_tex_color(image, tex_x, tex_y);
        pixel_put(game, x, y, color);
    }
}

void	drawing(t_game *game, int x)
{
	int line_height = (int)(HEIGHT / game->pg->wall_dist);
	int draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0) draw_start = 0;
	int draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

	double wall_x;
	if (game->pg->side == 0) wall_x = game->pg->pos_y + game->pg->wall_dist * game->pg->ray_y;
	else wall_x = game->pg->pos_x + game->pg->wall_dist * game->pg->ray_x;
	wall_x -= floor(wall_x);
	game->pg->ray_x = game->pg->ray_x;
	game->pg->ray_y = game->pg->ray_y;
	render_wall_column(game, x, line_height, draw_start, draw_end, game->pg->side, wall_x);
}

int render_game(t_game *game)
{
	int x;

	x = -1;
    render_ceiling_and_floor(game);
	while (x < WIDTH)
    {
        calculate_ray_direction(game, x);
        identify_cell(game->pg);
        calculate_wall_distance(game);
		drawing(game, x);
		x++;
    }
    printf("Rendering frame...\n");
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    printf("Finished rendering frame.\n");
    return (0);
}
