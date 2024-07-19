/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:29:19 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/17 14:51:04 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_rectangle(t_game *game, int x, int y, int width, int height, int color)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            char *dst = game->addr + ((y + i) * game->line + (x + j) * (game->bits / 8));
            *(unsigned int *)dst = color;
        }
    }
}

void draw_health_bar(t_game *game, int x, int y, int width, int height)
{
    // Disegna il contorno della barra (sfondo)
    draw_rectangle(game, x - 2, y - 2, width + 4, height + 4, 0x555555); // Grigio scuro

    // Calcola la lunghezza della barra basata sulla vita del giocatore
    int health_width = (game->pg->health * width) / 100;

    // Disegna la parte riempita della barra
    draw_rectangle(game, x, y, health_width, height, 0xFF0000); // Rosso
}
