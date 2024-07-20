/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:34:55 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/20 19:06:55 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    set_player_direction(t_game *game, char dir)
{
    if (dir == NORTH) {
        game->pg->dir_x = 0;
        game->pg->dir_y = -1;
        game->pg->plane_x = 0.66;
        game->pg->plane_y = 0;
    } else if (dir == SOUTH) {
        game->pg->dir_x = 0;
        game->pg->dir_y = 1;
        game->pg->plane_x = -0.66;
        game->pg->plane_y = 0;
    } else if (dir == EAST) {
        game->pg->dir_x = 1;
        game->pg->dir_y = 0;
        game->pg->plane_x = 0;
        game->pg->plane_y = 0.66;
    } else if (dir == WEST) {
        game->pg->dir_x = -1;
        game->pg->dir_y = 0;
        game->pg->plane_x = 0;
        game->pg->plane_y = -0.66;
    }
}

void init_paths(t_game *game, char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    int i;

    i = 0;
    game->texture_paths = malloc(sizeof(char *) * MAX_TEXTURES);
    if (fd < 0)
    {
        printf("Error: Failed to open map file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // Leggi le prime 6 righe per le texture
    while (i < 6)
    {
        line = get_next_line(fd);
        if (line == NULL)
            continue;
        game->texture_paths[i] = ft_strdup(ft_strchr(line, 't'));
        free(line);
        i++;
    }
    if (!load_wall_textures(game))
    {
        printf("Error: Failed to load wall textures.\n");
        return ;
    }
    init_map(game, fd);
    close(fd);
}

void init_map(t_game *game, int fd)
{
    char *buffer[10000];
    int i, rows, max_cols;

    i = 0;
    get_next_line(fd);
    while ((buffer[i] = get_next_line(fd)) != NULL)
        i++;
    rows = i;
    max_cols = 0;
    for (i = 0; i < rows; i++)
    {
        int len = ft_strlen(buffer[i]);
        if (len > max_cols)
            max_cols = len;
    }
    game->map = malloc(sizeof(char *) * rows);
    for (i = 0; i < rows; i++)
    {
        game->map[rows - i - 1] = malloc(sizeof(char) * max_cols + 1);
        ft_bzero(game->map[rows - i - 1], max_cols, ' ');
        strcpy(game->map[rows - i - 1], buffer[i]);
        free(buffer[i]);
    }
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < max_cols; x++)
        {
            if (game->map[y][x] == NORTH || game->map[y][x] == SOUTH || game->map[y][x] == EAST || game->map[y][x] == WEST)
            {
                game->pg->pos_x = x + 0.5;
                game->pg->pos_y = y + 0.5;
                set_player_direction(game, game->map[y][x]);
                game->map[y][x] = '0';
            }
            else if (game->map[y][x] == FLY || game->map[y][x] == SPIDER || game->map[y][x] == CROW)
                game->num_enemies++;
            else if (game->map[y][x] == FOOD || game->map[y][x] == BONE)
                game->num_food++;
            else if (game->map[y][x] == DOOR)
            {
                game->door_x = x;
                game->door_y = y;
                game->map[y][x] = '1';
            }
        }
    }
    game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
    game->food = malloc(sizeof(t_food) * game->num_food);
    game->cat = malloc(sizeof(t_cat));
    int enemy_index = 0;
    int food_index = 0;
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < max_cols; x++)
        {
            if (game->map[y][x] == FOOD)
            {
                game->food[food_index].texture = game->tex->food;
                game->food[food_index].type = 0;
            }
            else if (game->map[y][x] == BONE)
            {
                game->food[food_index].texture = game->tex->bone;
                game->food[food_index].type = 1;
            }
            if (game->map[y][x] == FOOD || game->map[y][x] == BONE)
            {
                game->food[food_index].pos_x = x + 0.5;
                game->food[food_index].pos_y = y + 0.5;
                food_index++;
            }
        }
    }
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < max_cols; x++)
        {
            if (game->map[y][x] == FLY)
            {
                game->enemies[enemy_index].texture = game->tex->fly;
                game->enemies[enemy_index].texture2 = game->tex->fly_open;
                game->enemies[enemy_index].attack_texture = game->tex->fly_attack;
                game->enemies[enemy_index].dead_texture = game->tex->fly_dead;
                game->enemies[enemy_index].enemy_health = 100;
                game->enemies[enemy_index].type = FLY;
            }
            else if (game->map[y][x] == SPIDER)
            {
                game->enemies[enemy_index].texture = game->tex->spider;
                game->enemies[enemy_index].texture2 = game->tex->spider_2;
                game->enemies[enemy_index].attack_texture = game->tex->spider_attack;
                game->enemies[enemy_index].dead_texture = game->tex->spider_dead;
                game->enemies[enemy_index].enemy_health = 100;
                game->enemies[enemy_index].type = SPIDER;
            }
            else if (game->map[y][x] == CROW)
            {
                game->enemies[enemy_index].texture = game->tex->crow;
                game->enemies[enemy_index].texture2 = game->tex->crow_open;
                game->enemies[enemy_index].attack_texture = game->tex->crow_attack;
                game->enemies[enemy_index].dead_texture = game->tex->crow_dead;
                game->enemies[enemy_index].enemy_health = 100;
                game->enemies[enemy_index].type = CROW;
            }
            if (game->map[y][x] == FLY || game->map[y][x] == SPIDER || game->map[y][x] == CROW)
            {
                game->enemies[enemy_index].pos_x = x + 0.5;
                game->enemies[enemy_index].pos_y = y + 0.5;
                game->enemies[enemy_index].current_texture = game->enemies[enemy_index].texture;
                game->enemies[enemy_index].last_switch_time = 0;
                game->enemies[enemy_index].death_timer = -1;
                enemy_index++;
            }
        }
    }
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < max_cols; x++)
        {
            if (game->map[y][x] == CAT)
            {
                game->cat->pos_x = x + 0.5;
                game->cat->pos_y = y + 0.5;
                game->cat->escape_texture = game->tex->cat_escape;
                game->cat->current_texture = game->cat->escape_texture;
                game->cat->escape_texture_2 = game->tex->cat_escape_2;
                game->cat->escape_texture_3 = game->tex->cat_escape_3;
                game->cat->escape_texture_4 = game->tex->cat_escape_4;
                game->cat->dead_texture = game->tex->cat_dead;
                game->cat->health = 500;
                game->cat->death_timer = -1;
                game->cat->visible = 0;
                game->cat->wait_timer = 5;
                game->cat->moving = 1;
                game->cat->target_x = game->door_x + 0.5;
                game->cat->target_y = game->door_y + 0.5;
                game->map[y][x] = '0';
            }
        }
    }
}
