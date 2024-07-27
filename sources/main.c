/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:29:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 12:48:02 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    exit_game(t_game *g)
{
    // fare if prima del free
    free(g->pg);
    free(g->tex->sky);
    free(g->tex->floor);
    free(g->tex->north);
    free(g->tex->south);
    free(g->tex->west);
    free(g->tex->east);
    free(g->tex->paws);
    free(g->tex->blood_paws);
    free(g->tex->maya);
    free(g->tex->maya_left);
    free(g->tex->maya_right);
    free(g->tex->angry_maya);
    free(g->tex->crow);
    free(g->tex->fly);
    free(g->tex->spider);
    free(g->tex->crow_open);
    free(g->tex->fly_open);
    free(g->tex->spider_2);
    free(g->tex->fly_attack);
    free(g->tex->spider_attack);
    free(g->tex->crow_attack);
    free(g->tex->fly_dead);
    free(g->tex->spider_dead);
    free(g->tex->crow_dead);
    free(g->tex->food);
    free(g->tex->bone);
    free(g->tex->cat_dead);
    free(g->tex->cat_escape);
    free(g->tex->cat_escape_2);
    free(g->tex->cat_escape_3);
    free(g->tex->cat_escape_4);
    free(g->tex->cat_face);
    free(g->tex->open_door);
    free(g->tex->closed_door);
    free(g->tex);
    free(g->map);
    free(g->enemies);
    free(g->food);
    free(g->cat);
    free(g->texture_paths);
    mlx_clear_window(g->mlx, g->win);
    mlx_destroy_window(g->mlx, g->win);
    exit(0);
}

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
    game->minimap = mlx_new_image(game->mlx, game->map_width, game->map_height);
    game->miniaddr = mlx_get_data_addr(game->minimap, &game->minibits, &game->miniline, &game->miniendian);
    game->pg = malloc(sizeof(t_player));
    game->frame_count = 0;
    if (!game->pg)
        return ;
    game->pg->health = 100;
    game->tex = malloc(sizeof(t_texture));
    if (!game->tex)
    {
        free(game->pg);
        return ;
    }
    game->face_state = 0;
    game->face_timer = 300;
    game->num_doors = 0;
    game->num_enemies = 0;
    game->num_food = 0;
    game->show_minimap = 0;
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

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        return (0);
    init_game(&game);
    load_textures_and_map(&game, argv[1]);
    game.pg->move_speed = 0.12;
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    render_ceiling_and_floor(&game);
    mlx_loop_hook(game.mlx, &render_game, &game);
    mlx_loop(game.mlx);
    return 0;
}
