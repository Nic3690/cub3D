/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:37:36 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 11:05:11 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    mini_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    dst = game->miniaddr + (y * game->miniline + x * (game->minibits / 8));
    *(unsigned int *)dst = color;
}

void    draw_square(t_game *game, int x, int y, int color)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            mini_pixel_put(game, (x + i), (y + j), color);
            j++;
        }
        i++;
    }
}

void    draw_mini_player(t_game *g)
{
    int player_mini_x;
    int player_mini_y;

    player_mini_x = g->pg->pos_x;
    player_mini_y = g->pg->pos_y;
    draw_square(g, player_mini_x * TILE_SIZE, player_mini_y
        * TILE_SIZE, 0xFF0000);
}

void    draw_mini_cat(t_game *g)
{
    int cat_mini_x;
    int cat_mini_y;

    cat_mini_x = g->cat->pos_x;
    cat_mini_y = g->cat->pos_y;
    draw_square(g, cat_mini_x * TILE_SIZE, cat_mini_y
        * TILE_SIZE, 0x00FF00);
}

void    draw_minimap(t_game *g)
{
    int x;
    int y;

    x = 0;
    y = 0;
    mlx_destroy_image(g->mlx, g->minimap);
    g->minimap = mlx_new_image(g->mlx, WIDTH, HEIGHT);
    g->miniaddr = mlx_get_data_addr(g->minimap, &g->minibits, &g->miniline, &g->miniendian);
    while (y < g->map_cols)
    {
        x = 0;
        while (x < g->map_rows)
        {
            if (g->map[x][y] == '1')
                draw_square(g, y * TILE_SIZE, x * TILE_SIZE, 0xFFFFFF);
            x++;
        }
        y++;
    }
    draw_mini_player(g);
    if (g->is_cat)
        draw_mini_cat(g);
    mlx_put_image_to_window(g->mlx, g->win, g->minimap, 0, 0);
}
