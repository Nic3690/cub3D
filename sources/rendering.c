/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:11 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/26 15:28:24 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void render_wall_column(t_game *g, int x, int side)
{
    t_image *image;
    double tex_pos;

    if (g->pg->map_x == g->door_x && g->pg->map_y == g->door_y)
        image = g->tex->door_light;
    else
        if (side == 0 && g->pg->ray_x > 0)
            image = g->tex->east;
        else if (side == 0 && g->pg->ray_x < 0)
            image = g->tex->west;
        else if (side == 1 && g->pg->ray_y > 0)
            image = g->tex->south;
        else
            image = g->tex->north;
    for (int i = 0; i < g->num_doors; i++)
    {
        if (g->pg->map_x == g->doors[i].pos_x && g->pg->map_y == g->doors[i].pos_y)
            image = g->doors[i].curr_tex;
    }
    g->tex->tex_w = image->w;
    g->tex->tex_h = image->h;
    g->draw->tex_x = (int)(g->draw->wall_x * (double)g->tex->tex_w);
    if (side == 0 && g->pg->ray_x > 0)
        g->draw->tex_x = g->tex->tex_w - g->draw->tex_x - 1;
    if (side == 1 && g->pg->ray_y < 0)
        g->draw->tex_x = g->tex->tex_w - g->draw->tex_x - 1;
    g->draw->step = 1.0 * g->tex->tex_w / g->draw->line;
    tex_pos = (g->draw->draw_start - HEIGHT / 2 + g->draw->line / 2) * g->draw->step;
    drawing(g, image, tex_pos, x);
}

void render(t_game *g)
{
    int x;

    x = 0;
    while (x < WIDTH)
    {
        calculate_ray_direction(g, x);
        identify_cell(g->pg);
        calculate_wall_distance(g, 1);
        drawing_colums(g, x);
        g->z_buffer[x] = g->pg->wall_dist;
        x++;
    }
}

void    render_doors(t_game *g)
{
    int x;

    x = 0;
    while (x < WIDTH)
    {
        calculate_ray_direction(g, x);
        identify_cell(g->pg);
        calculate_wall_distance(g, 9);
        drawing_colums(g, x);
        g->z_buffer[x] = g->pg->wall_dist;
        x++;
    }
}

int render_game(t_game *game)
{
    game->z_buffer = malloc(sizeof(double) * WIDTH);
    render_ceiling_and_floor(game);
    render(game);
    render_doors(game);
    int entity_count = game->num_food + game->num_enemies + 1;
    if (!game->is_cat)
        entity_count--;
    t_entity *entities = malloc(sizeof(t_entity) * entity_count);
    entity_distances(game, entities, &entity_count);
    update_cat_textures(game);
    update_enemy_textures(game);
    update_food_textures(game);
    check_food_collision(game);
    for (int i = 0; i < entity_count; i++)
        render_entity(game, &entities[i]);

    free(entities);

    draw_paws_attack(game);
    draw_health_bar(game, WIDTH / 13, HEIGHT / 9, 3 * WIDTH / 10, HEIGHT / 60);
    draw_health_bar_cat(game, WIDTH - (3 * WIDTH / 10) - (WIDTH / 13), HEIGHT / 9, 3 * WIDTH / 10, HEIGHT / 60);
    update_face_state(game);
    draw_face(game);
    draw_face_cat(game);
    if (game->show_minimap)
        draw_minimap(game);
    else
        mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    free(game->z_buffer);
    game->frame_count++;
    return (0);
}