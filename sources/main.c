/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:29:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/06/30 15:19:00 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
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
    game->player = malloc(sizeof(t_player));
    if (!game->player)
        return ;
    game->texture = malloc(sizeof(t_texture));
    if (!game->texture)
    {
        free(game->player);
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
    image->width = width;
    image->height = height;
    return 1;
}

int load_wall_textures(t_game *game, const char **paths)
{
    game->texture->sky = malloc(sizeof(t_image));
    game->texture->floor = malloc(sizeof(t_image));
    game->texture->north = malloc(sizeof(t_image));
    game->texture->south = malloc(sizeof(t_image));
    game->texture->west = malloc(sizeof(t_image));
    game->texture->east = malloc(sizeof(t_image));
    load_texture(game, game->texture->sky, paths[0]);
    load_texture(game, game->texture->floor, paths[1]);
    load_texture(game, game->texture->north, paths[2]);
    load_texture(game, game->texture->south, paths[3]);
    load_texture(game, game->texture->west, paths[4]);
    load_texture(game, game->texture->east, paths[5]);
    return (1);
}

int main(int argc, char **argv)
{
    t_game game;

    const char *texture_paths[] = {
        "textures/sky.xpm",
        "textures/grass.xpm",
        "textures/Recinto.xpm",
        "textures/recintodark.xpm",
        "textures/fence_light.xpm",
        "textures/fence_dark.xpm"
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
    game.player->pos_x = 22.0;
    game.player->pos_y = 12.0;
    game.player->dir_x = -1.0;
    game.player->dir_y = 0.0;
    game.player->plane_x = 0.0;
    game.player->plane_y = 0.66;
    load_map(&game, "./maps/map.txt");
    render_game(&game);
    // mlx_loop_hook(game.mlx, &render_game, &game);
    mlx_loop(game.mlx);
    free(game.player);
    free(game.texture->sky);
    free(game.texture->floor);
    free(game.texture->north);
    free(game.texture->south);
    free(game.texture->west);
    free(game.texture->east);
    free(game.texture);
    return 0;
    (void)argv;
}
