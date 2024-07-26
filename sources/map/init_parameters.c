/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:55:49 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 00:02:30 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    init_doors(t_game *game)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < game->map_rows)
    {
        x = 0;
        while (x < game->map_cols)
        {
            check_doors(game, x, y);
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
