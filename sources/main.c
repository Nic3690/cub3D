/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:29:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/13 23:25:26 by nfurlani         ###   ########.fr       */
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

void init_game(t_game *game)
{
    game->map_width = WIDTH;
    game->map_height = HEIGHT;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, game->map_width, game->map_height, "Cub3D");
    game->img = mlx_new_image(game->mlx, game->map_width, game->map_height);
    game->addr = mlx_get_data_addr(game->img, &game->bits, &game->line, &game->endian);
    game->pg = malloc(sizeof(t_player));
    if (!game->pg)
        return ;
    game->tex = malloc(sizeof(t_texture));
    if (!game->tex)
    {
        free(game->pg);
        return ;
    }
}

int load_texture(t_game *game, t_image *image, const char *path)
{
    int width;
    int height;

    width = 64;
    height = 64;
    image->img = mlx_xpm_file_to_image(game->mlx, (char *)path, &width, &height);
    if (!image->img)
        return 0;
    image->addr = mlx_get_data_addr(image->img, &image->bits, &image->line, &image->endian);
    if (!image->addr)
    {
        mlx_destroy_image(game->mlx, game->image->img);
        return 0;
    }
    image->w = width;
    image->h = height;
    return 1;
}

int load_wall_textures(t_game *game, const char **paths)
{
    game->tex->sky = malloc(sizeof(t_image));
    game->tex->floor = malloc(sizeof(t_image));
    game->tex->north = malloc(sizeof(t_image));
    game->tex->south = malloc(sizeof(t_image));
    game->tex->west = malloc(sizeof(t_image));
    game->tex->east = malloc(sizeof(t_image));
    game->tex->paws = malloc(sizeof(t_image));
    game->tex->enemy = malloc(sizeof(t_image));
    load_texture(game, game->tex->sky, paths[0]);
    load_texture(game, game->tex->floor, paths[1]);
    load_texture(game, game->tex->north, paths[2]);
    load_texture(game, game->tex->south, paths[3]);
    load_texture(game, game->tex->west, paths[4]);
    load_texture(game, game->tex->east, paths[5]);
    load_texture(game, game->tex->paws, "textures/tranquipaws.xpm");
    load_texture(game, game->tex->enemy, "textures/crow_closed.xpm");
    return (1);
}

int main(int argc, char **argv)
{
    t_game game;

    const char *texture_paths[] = {
        "textures/sky.xpm",
        "textures/grass.xpm",
        "textures/Recinto.xpm",
        "textures/fence_dark.xpm",
        "textures/recintodark.xpm",
        "textures/fence_light.xpm"
    };
    (void)argc;
    // if (argc != 2)
    //     return (0);
    init_game(&game);
    if (!load_wall_textures(&game, texture_paths))
    {
        printf("Error: Failed to load wall textures.\n");
        return 1;
    }
    game.pg->dir_x = 0.5;
    game.pg->dir_y = 0.0;
    game.pg->plane_x = 0.0;
    game.pg->plane_y = 0.66;
    game.pg->move_speed = 0.12;
    init_paths(&game, "./maps/map.cub");
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    render_ceiling_and_floor(&game);
    mlx_loop_hook(game.mlx, &render_game, &game);
    mlx_loop(game.mlx);
    free(game.pg);
    free(game.tex->sky);
    free(game.tex->floor);
    free(game.tex->north);
    free(game.tex->south);
    free(game.tex->west);
    free(game.tex->east);
    free(game.tex->paws);
    free(game.tex);
    return 0;
    (void)argv;
}
