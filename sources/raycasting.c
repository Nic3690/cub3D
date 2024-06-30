/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:13:41 by nfurlani          #+#    #+#             */
/*   Updated: 2024/06/30 15:57:04 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void render_ceiling_and_floor(t_game *game)
{
    t_image *ceiling_texture = game->texture->sky;
    t_image *floor_texture = game->texture->floor;

    for (int y = 0; y < HEIGHT; y++)
    {
        int is_ceiling = (y < HEIGHT / 2);
        t_image *texture = is_ceiling ? ceiling_texture : floor_texture;
        int texture_height = texture->height;
        int texture_width = texture->width;

        double ray_dir_x0 = game->player->dir_x - game->player->plane_x;
        double ray_dir_y0 = game->player->dir_y - game->player->plane_y;
        double ray_dir_x1 = game->player->dir_x + game->player->plane_x;
        double ray_dir_y1 = game->player->dir_y + game->player->plane_y;

        int p = is_ceiling ? y : HEIGHT - y - 1;
        double pos_z = 0.5 * HEIGHT;
        double row_distance = pos_z / (p - HEIGHT / 2);

        double floor_step_x = row_distance * (ray_dir_x1 - ray_dir_x0) / WIDTH;
        double floor_step_y = row_distance * (ray_dir_y1 - ray_dir_y0) / WIDTH;

        double floor_x = game->player->pos_x + row_distance * ray_dir_x0;
        double floor_y = game->player->pos_y + row_distance * ray_dir_y0;

        for (int x = 0; x < WIDTH; x++)
        {
            int tex_x = (int)(texture_width * (floor_x - (int)floor_x)) & (texture_width - 1);
            int tex_y = (int)(texture_height * (floor_y - (int)floor_y)) & (texture_height - 1);
            floor_x += floor_step_x;
            floor_y += floor_step_y;

            int color = get_texture_pixel_color(texture, tex_x, tex_y);
            my_mlx_pixel_put(game, x, y, is_ceiling ? color : color);
        }
    }
}

void calculate_ray_direction(t_game *game, int x, double *ray_dir_x, double *ray_dir_y)
{
    double camera_x = 2 * x / (double)WIDTH - 1;
    *ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
    *ray_dir_y = game->player->dir_y + game->player->plane_y * camera_x;
}

void identify_map_cell(t_player *player, double ray_dir_x, double ray_dir_y, int *map_x, int *map_y)
{
    *map_x = (int)player->pos_x;
    *map_y = (int)player->pos_y;

    double delta_dist_x = (ray_dir_x != 0) ? fabs(1 / ray_dir_x) : DBL_MAX;
    double delta_dist_y = (ray_dir_y != 0) ? fabs(1 / ray_dir_y) : DBL_MAX;

    int step_x = (ray_dir_x < 0) ? -1 : 1;
    int step_y = (ray_dir_y < 0) ? -1 : 1;

    if (ray_dir_x < 0)
        player->side_dist_x = (player->pos_x - *map_x) * delta_dist_x;
    else
        player->side_dist_x = (*map_x + 1.0 - player->pos_x) * delta_dist_x;

    if (ray_dir_y < 0)
        player->side_dist_y = (player->pos_y - *map_y) * delta_dist_y;
    else
        player->side_dist_y = (*map_y + 1.0 - player->pos_y) * delta_dist_y;

    player->step_x = step_x;
    player->step_y = step_y;
}

void calculate_wall_distance(t_game *game, double ray_dir_x, double ray_dir_y, int *map_x, int *map_y, int *side, double *wall_dist)
{
    double side_dist_x, side_dist_y;
    double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
    double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

    int step_x = (ray_dir_x < 0) ? -1 : 1;
    int step_y = (ray_dir_y < 0) ? -1 : 1;

    if (ray_dir_x < 0)
        side_dist_x = (game->player->pos_x - *map_x) * delta_dist_x;
    else
        side_dist_x = (*map_x + 1.0 - game->player->pos_x) * delta_dist_x;

    if (ray_dir_y < 0)
        side_dist_y = (game->player->pos_y - *map_y) * delta_dist_y;
    else
        side_dist_y = (*map_y + 1.0 - game->player->pos_y) * delta_dist_y;

    int hit = 0;
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            *map_x += step_x;
            *side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            *map_y += step_y;
            *side = 1;
        }
        if (game->map[*map_y][*map_x] == '1')
            hit = 1; // Controlla se il raggio ha colpito un muro
    }

    if (*side == 0)
        *wall_dist = (*map_x - game->player->pos_x + (1 - step_x) / 2) / ray_dir_x;
    else
        *wall_dist = (*map_y - game->player->pos_y + (1 - step_y) / 2) / ray_dir_y;
}

int calculate_line_height(t_player *player, int side)
{
    double wall_dist = (side == 0) ?
        (player->map_x - player->pos_x + (1 - player->step_x) / 2) / player->ray_dir_x :
        (player->map_y - player->pos_y + (1 - player->step_y) / 2) / player->ray_dir_y;
    return (int)(HEIGHT / wall_dist);
}

int get_texture_pixel_color(t_image *image, int tex_x, int tex_y)
{
    int *texture = (int *)image->addr;
    return texture[tex_y * image->width + tex_x];
}

void render_wall_column(t_game *game, int x, int line_height, int draw_start, int draw_end, int side, double wall_x)
{
    t_image *image;
    if (side == 0 && game->player->ray_dir_x > 0)
        image = game->texture->east;
    else if (side == 0 && game->player->ray_dir_x < 0)
        image = game->texture->west;
    else if (side == 1 && game->player->ray_dir_y > 0)
        image = game->texture->south;
    else
        image = game->texture->north;

    int texture_width = image->width;
    int texture_height = image->height;

    int tex_x = (int)(wall_x * (double)texture_width);
    if (side == 0 && game->player->ray_dir_x > 0) tex_x = texture_width - tex_x - 1;
    if (side == 1 && game->player->ray_dir_y < 0) tex_x = texture_width - tex_x - 1;

    double step = 1.0 * texture_height / line_height;
    double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;

    for (int y = draw_start; y < draw_end; y++)
    {
        int tex_y = (int)tex_pos & (texture_height - 1);
        tex_pos += step;
        int color = get_texture_pixel_color(image, tex_x, tex_y);
        my_mlx_pixel_put(game, x, y, color);
    }
}

int render_game(t_game *game)
{
    render_ceiling_and_floor(game);
    for (int x = 0; x < WIDTH; x++)
    {
        double ray_dir_x, ray_dir_y;
        calculate_ray_direction(game, x, &ray_dir_x, &ray_dir_y);

        int map_x, map_y;
        identify_map_cell(game->player, ray_dir_x, ray_dir_y, &map_x, &map_y);

        int side;
        double wall_dist;
        calculate_wall_distance(game, ray_dir_x, ray_dir_y, &map_x, &map_y, &side, &wall_dist);

        int line_height = (int)(HEIGHT / wall_dist);
        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        double wall_x;
        if (side == 0) wall_x = game->player->pos_y + wall_dist * ray_dir_y;
        else wall_x = game->player->pos_x + wall_dist * ray_dir_x;
        wall_x -= floor(wall_x);

        game->player->ray_dir_x = ray_dir_x;
        game->player->ray_dir_y = ray_dir_y;
        render_wall_column(game, x, line_height, draw_start, draw_end, side, wall_x);
    }

    printf("Rendering frame...\n");
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    printf("Finished rendering frame.\n");
    return (0);
}