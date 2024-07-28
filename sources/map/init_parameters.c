/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:55:49 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 15:50:41 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    init_doors(t_game *game)
{
    int x;
    int y;
    int index;

    x = 0;
    y = 0;
    index = 0;
    while (y < game->map_rows)
    {
        x = 0;
        while (x < game->map_cols)
        {
            check_doors(game, x, y, &index);
            x++;
        }
        y++;
    }
}

void    init_food(t_game *game)
{
    int x;
    int y;
    int index;

    x = 0;
    y = 0;
    index = 0;
    while (y < game->map_rows)
    {
        x = 0;
        while (x < game->map_cols)
        {
            check_food(game, x, y, &index);
            x++;
        }
        y++;
    }
}

void    init_enemies(t_game *game)
{
    int x;
    int y;
    int index;

    x = 0;
    y = 0;
    index = 0;
    while (y < game->map_rows)
    {
        x = 0;
        while (x < game->map_cols)
        {
            check_and_set_enemy(game, x, y, &index);
            x++;
        }
        y++;
    }
}

void    get_next_coords(t_game *game, int *start_x, int *start_y)
{
    int original_x = *start_x;
    int original_y = *start_y;

    if (original_x + 1 < game->map_cols && game->map[original_y][original_x + 1] == '%')
        *start_x = original_x + 1;
    else if (original_x - 1 >= 0 && game->map[original_y][original_x - 1] == '%')
        *start_x = original_x - 1;
    else if (original_y + 1 < game->map_rows && game->map[original_y + 1][original_x] == '%')
        *start_y = original_y + 1;
    else if (original_y - 1 >= 0 && game->map[original_y - 1][original_x] == '%')
        *start_y = original_y - 1;
}

// new function
void    add_path_coordinates(t_game *game)
{
    int start_x;
    int start_y;

    start_x = game->cat->map_x + 1;
    start_y = game->cat->map_y;
    
    while (game->cat->path_length < MAX_PATH_LENGTH)
    {
        game->map[start_y][start_x] = '0';
        get_next_coords(game, &start_x, &start_y);
        game->cat->path[game->cat->path_length].x = start_x;
        game->cat->path[game->cat->path_length].y = start_y;
        game->cat->path_length++;
    }
    game->cat->path[game->cat->path_length].x = game->door_x;
    game->cat->path[game->cat->path_length].y = game->door_y;
}

// modified function
void    init_cat(t_game *game)
{
    int x, y;

    y = 0;
    game->is_cat = 0;
    while (y < game->map_rows)
    {
        x = 0;
        while (x < game->map_cols)
        {
            if (game->map[y][x] == CAT)
                set_cat_properties(game, x, y);
            x++;
        }
        y++;
    }
    if (game->is_cat)
        add_path_coordinates(game);
}

void    init_map(t_game *game, int fd)
{
    char    *buffer[10000];

    get_rows_and_cols(game, fd, buffer);
    copy_map(game, buffer);
    scan_map_for_entities(game);
    allocate_entities(game);
    init_doors(game);
    init_food(game);
    init_enemies(game);
    init_cat(game);
}
