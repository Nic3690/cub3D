/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:29:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 11:13:24 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = game->addr + (y * game->line + x * (game->bits / 8));
	*(unsigned int *)dst = color;
}

void    init_parameters_game(t_game *g)
{
    g->frame_count = 0;
    g->pg->health = 100;
    g->face_state = 0;
    g->face_timer = 300;
    g->num_doors = 0;
    g->num_enemies = 0;
    g->num_food = 0;
    g->show_minimap = 0;
    g->win_status = 0;
}

void init_game(t_game *g)
{   
    g->map_width = WIDTH;
    g->map_height = HEIGHT;
    g->mlx = mlx_init();
    g->win = mlx_new_window(g->mlx, g->map_width, g->map_height, "Cub3D");
    g->img = mlx_new_image(g->mlx, g->map_width, g->map_height);
    g->addr = mlx_get_data_addr(g->img, &g->bits, &g->line, &g->endian);
    g->minimap = mlx_new_image(g->mlx, g->map_width, g->map_height);
    g->miniaddr = mlx_get_data_addr(g->minimap, &g->minibits, &g->miniline, &g->miniendian);
    g->pg = malloc(sizeof(t_player));
    if (!g->pg)
        exit_game(g);
    g->tex = malloc(sizeof(t_texture));
    init_parameters_game(g);
    if (!g->tex)
        exit_game(g);
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        return (0);
    init_game(&game);
    load_textures_and_map(&game, argv[1]);
    //check_valid_map(&game);
    game.pg->move_speed = 0.12;
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    render_ceiling_and_floor(&game);
    mlx_loop_hook(game.mlx, &render_game, &game);
    mlx_loop(game.mlx);
    return 0;
}
