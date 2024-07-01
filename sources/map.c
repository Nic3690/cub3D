/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:34:55 by nfurlani          #+#    #+#             */
/*   Updated: 2024/06/30 19:04:36 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void load_map(t_game *game, const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Failed to open map file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char buffer[MAP_ROWS][MAP_COLUMNS + 1];
    for (int i = 0; i < MAP_ROWS; i++)
    {
        if (read(fd, buffer[i], MAP_COLUMNS + 1) >= MAP_COLUMNS + 2) // +1 for the newline character
        {
            printf("Error: Failed to read map line %d\n", i);
            close(fd);
            exit(EXIT_FAILURE);
        }
        buffer[i][MAP_COLUMNS] = '\0'; // Ensure null-termination
    }
    close(fd);

    // Initialize the game map and pg position
    for (int y = 0; y < MAP_ROWS; y++)
    {
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            if (buffer[y][x] == 'P')
            {
                game->pg->pos_x = x + 0.5;
                game->pg->pos_y = y + 0.5;
                buffer[y][x] = '0'; // Clear the pg's starting position in the map
            }
        }
    }

    // Store the map in the game structure
    game->map = malloc(sizeof(char *) * MAP_ROWS);
    for (int y = 0; y < MAP_ROWS; y++)
    {
        game->map[y] = malloc(MAP_COLUMNS + 1);
        for (int x = 0; x < MAP_COLUMNS; x++)
        {
            game->map[y][x] = buffer[y][x];
        }
        game->map[y][MAP_COLUMNS] = '\0'; // Null-terminate each line
    }
}
