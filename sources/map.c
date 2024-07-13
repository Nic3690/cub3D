/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:34:55 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/13 23:55:14 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
    init_map(game, fd);
    close(fd);
}

void init_map(t_game *game, int fd)
{
    // char **temp_map;
    char *buffer[10000];
    int i, rows, max_cols;

    // Leggi la mappa dal file in un buffer temporaneo
    i = 0;
    get_next_line(fd); // Salta le righe delle texture
    while ((buffer[i] = get_next_line(fd)) != NULL)
        i++;
    rows = i;
    // Determina la larghezza massima della mappa
    max_cols = 0;
    for (i = 0; i < rows; i++)
    {
        int len = ft_strlen(buffer[i]);
        if (len > max_cols)
            max_cols = len;
    }
    // Alloca memoria per la mappa temporanea
    game->map = malloc(sizeof(char *) * rows);
    for (i = 0; i < rows; i++)
    {
        game->map[rows - i - 1] = ft_strdup(buffer[i]);
        free(buffer[i]);
    }
    printf ("Rows: %d\n Max_cols: %d\n", rows, max_cols);
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < max_cols; x++)
        {
            if (game->map[y][x] == 'P')
            {
                printf("Player found at %d, %d\n", x, y);
                game->pg->pos_x = x + 0.5;
                game->pg->pos_y = y + 0.5;
                game->map[y][x] = '0';
            }
            if (game->map[y][x] == 'E')
                game->num_enemies++;
        }
    }
    game->enemies = malloc(sizeof(t_enemy) * game->num_enemies);
    int enemy_index = 0;
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < max_cols; x++)
        {
            if (game->map[y][x] == 'E')
            {
                game->enemies[enemy_index].pos_x = x + 0.5;
                game->enemies[enemy_index].pos_y = y + 0.5;
                game->enemies[enemy_index].texture = game->tex->enemy;
                enemy_index++;
            }
        }
    }
}
