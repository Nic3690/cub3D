/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:29:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/21 13:43:08 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    exit_game(t_game *g)
{
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
    free(g->enemies); // liberare i contenuti
    free(g->food); // liberare i contenuti
    free(g->cat);
    free(g->texture_paths); // liberare i contenuti
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

int load_wall_textures(t_game *game)
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
    game->tex->food = malloc(sizeof(t_image));
    game->tex->bone = malloc(sizeof(t_image));
    game->tex->cat_dead = malloc(sizeof(t_image));
    game->tex->cat_escape = malloc(sizeof(t_image));
    game->tex->cat_escape_2 = malloc(sizeof(t_image));
    game->tex->cat_escape_3 = malloc(sizeof(t_image));
    game->tex->cat_escape_4 = malloc(sizeof(t_image));
    game->tex->cat_face = malloc(sizeof(t_image));
    game->tex->door_light = malloc(sizeof(t_image));
    game->tex->open_door = malloc(sizeof(t_image));
    game->tex->closed_door = malloc(sizeof(t_image));
    load_texture(game, game->tex->east, game->texture_paths[0]);
    load_texture(game, game->tex->south, game->texture_paths[1]);
    load_texture(game, game->tex->north, game->texture_paths[2]);
    load_texture(game, game->tex->west, game->texture_paths[3]);
    load_texture(game, game->tex->floor, game->texture_paths[4]);
    load_texture(game, game->tex->sky, game->texture_paths[5]);
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
    load_texture(game, game->tex->food, "textures/food.xpm");
    load_texture(game, game->tex->bone, "textures/bone.xpm");
    load_texture(game, game->tex->cat_dead, "textures/mismisvola.xpm");
    load_texture(game, game->tex->cat_escape, "textures/misescaping_1.xpm");
    load_texture(game, game->tex->cat_escape_2, "textures/misescaping_2.xpm");
    load_texture(game, game->tex->cat_escape_3, "textures/mismisescapediculo.xpm");
    load_texture(game, game->tex->cat_escape_4, "textures/mismisescapediculo_2.xpm");
    load_texture(game, game->tex->door_light, "textures/cat_door_light.xpm");
    load_texture(game, game->tex->cat_face, "textures/mismis_face.xpm");
    load_texture(game, game->tex->closed_door, "textures/gate_light.xpm");
    load_texture(game, game->tex->open_door, "textures/gate_light_open.xpm");
    return (1);
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        return (0);
    init_game(&game);
    init_paths(&game, argv[1]);
    game.pg->move_speed = 0.12;
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    render_ceiling_and_floor(&game);
    mlx_loop_hook(game.mlx, &render_game, &game);
    mlx_loop(game.mlx);
    return 0;
}
