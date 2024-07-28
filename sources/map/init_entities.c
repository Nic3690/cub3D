/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:54:40 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 20:19:55 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    increment_entity_counts(t_game *game, int x, int y)
{
    if (game->map[y][x] == FLY || game->map[y][x] == SPIDER
        || game->map[y][x] == CROW)
        game->num_enemies++;
    else if (game->map[y][x] == FOOD || game->map[y][x] == BONE)
        game->num_food++;
    else if (game->map[y][x] == DOOR)
        game->num_doors++;
}

void    scan_map_for_entities(t_game *game)
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
            if (game->map[y][x] == NORTH || game->map[y][x] == SOUTH
                || game->map[y][x] == EAST || game->map[y][x] == WEST)
                handle_player_position(game, x, y);
            else if (game->map[y][x] == CATDOOR)
                handle_door_position(game, x, y);
            else
                increment_entity_counts(game, x, y);
            x++;
        }
        y++;
    }
}

void    allocate_entities(t_game *game)
{
    game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
    if (game->enemies == NULL)
        exit(EXIT_FAILURE);
    game->food = malloc(sizeof(t_food) * game->num_food);
    if (game->food == NULL)
        exit(EXIT_FAILURE);
    game->doors = malloc(sizeof(t_door) * game->num_doors);
    if (game->doors == NULL)
        exit(EXIT_FAILURE);
    game->cat = malloc(sizeof(t_cat));
    if (game->cat == NULL)
        exit(EXIT_FAILURE);    
}
