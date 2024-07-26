/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:37:36 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/23 09:18:18 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define MINIMAP_SIZE 200
#define TILE_SIZE 300 / MAP_COLUMNS

void mini_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = game->miniaddr + (y * game->miniline + x * (game->minibits / 8));
    *(unsigned int *)dst = color;
}

void draw_square(t_game *game, int x, int y, int color)
{
    int i, j;

    for (i = 0; i < TILE_SIZE; i++) {
        for (j = 0; j < TILE_SIZE; j++) {
            mini_pixel_put(game, (x + i), (y + j), color);
        }
    }
}

void draw_minimap(t_game *game)
{
    int x, y;

    // Pulire la minimappa
    mlx_destroy_image(game->mlx, game->minimap);
    game->minimap = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->miniaddr = mlx_get_data_addr(game->minimap, &game->minibits, &game->miniline, &game->miniendian);

    for (y = 0; y < game->map_cols; y++) {
        for (x = 0; x < game->map_rows; x++) {
            if (game->map[x][y] == '1') {
                draw_square(game, y * TILE_SIZE, x * TILE_SIZE, 0xFFFFFF); // Bianco per i muri
            }
        }
    }
    int player_mini_x = game->pg->pos_x;
    int player_mini_y = game->pg->pos_y;
    draw_square(game, player_mini_x * TILE_SIZE, player_mini_y * TILE_SIZE, 0xFF0000); // Rosso per il giocatore

    if (game->is_cat) {
        int cat_mini_x = game->cat->pos_x;
        int cat_mini_y = game->cat->pos_y;
        draw_square(game, cat_mini_x * TILE_SIZE, cat_mini_y * TILE_SIZE, 0x00FF00); // Verde per il gatto
    }

    mlx_put_image_to_window(game->mlx, game->win, game->minimap, 0, 0);
}
