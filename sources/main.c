/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:29:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/19 17:16:51 by nfurlani         ###   ########.fr       */
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
    game->tex->blood_paws = malloc(sizeof(t_image));
    game->tex->crow = malloc(sizeof(t_image));
    game->tex->fly = malloc(sizeof(t_image));
    game->tex->spider = malloc(sizeof(t_image));
    game->tex->crow_open = malloc(sizeof(t_image));
    game->tex->fly_open = malloc(sizeof(t_image));
    game->tex->spider_2 = malloc(sizeof(t_image));
    game->tex->maya = malloc(sizeof(t_image));
    game->tex->maya_left = malloc(sizeof(t_image));
    game->tex->maya_right = malloc(sizeof(t_image));
    game->tex->angry_maya = malloc(sizeof(t_image));
    game->tex->fly_attack = malloc(sizeof(t_image));
    game->tex->spider_attack = malloc(sizeof(t_image));
    game->tex->crow_attack = malloc(sizeof(t_image));
    game->tex->fly_dead = malloc(sizeof(t_image));
    game->tex->spider_dead = malloc(sizeof(t_image));
    game->tex->crow_dead = malloc(sizeof(t_image));
    load_texture(game, game->tex->sky, paths[0]);
    load_texture(game, game->tex->floor, paths[1]);
    load_texture(game, game->tex->north, paths[2]);
    load_texture(game, game->tex->south, paths[3]);
    load_texture(game, game->tex->west, paths[4]);
    load_texture(game, game->tex->east, paths[5]);
    load_texture(game, game->tex->paws, "textures/paws.xpm");
    load_texture(game, game->tex->blood_paws, "textures/nontranquipaws.xpm");
    load_texture(game, game->tex->crow, "textures/crow_open.xpm");
    load_texture(game, game->tex->fly, "textures/fly_open.xpm");
    load_texture(game, game->tex->spider, "textures/spider_open.xpm");
    load_texture(game, game->tex->spider_2, "textures/spider_closed.xpm");
    load_texture(game, game->tex->crow_open, "textures/crow_closed.xpm");
    load_texture(game, game->tex->fly_open, "textures/fly_closed.xpm");
    load_texture(game, game->tex->maya, "textures/maya_1.xpm");
    load_texture(game, game->tex->maya_left, "textures/maya_2.xpm");
    load_texture(game, game->tex->maya_right, "textures/maya_3.xpm");
    load_texture(game, game->tex->angry_maya, "textures/angry_maya.xpm");
    load_texture(game, game->tex->fly_attack, "textures/fly_attack.xpm");
    load_texture(game, game->tex->spider_attack, "textures/spider_attack.xpm");
    load_texture(game, game->tex->crow_attack, "textures/crow_attack.xpm");
    load_texture(game, game->tex->fly_dead, "textures/poltigliadimosca.xpm");
    load_texture(game, game->tex->crow_dead, "textures/poltigliadicornacchia.xpm");
    load_texture(game, game->tex->spider_dead, "textures/poltigliadiragno.xpm");
    return (1);
}

int main(int argc, char **argv)
{
    t_game game;

    const char *texture_paths[] = {
        "textures/sky.xpm",
        "textures/grass.xpm",
        "textures/recinto.xpm",
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
    init_paths(&game, "./maps/test.cub");
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
    free(game.tex->blood_paws);
    free(game.tex->maya);
    free(game.tex->maya_left);
    free(game.tex->maya_right);
    free(game.tex->angry_maya);
    free(game.tex->crow);
    free(game.tex->fly);
    free(game.tex->spider);
    free(game.tex->crow_open);
    free(game.tex->fly_open);
    free(game.tex->spider_2);
    free(game.tex);
    return 0;
    (void)argv;
}
