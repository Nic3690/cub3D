/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:56:27 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/17 14:45:24 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void swap(t_enemy *a, t_enemy *b)
{
    t_enemy temp = *a;
    *a = *b;
    *b = temp;
}

int partition(t_enemy *arr, int low, int high)
{
    double pivot = arr[high].dist;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].dist > pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(t_enemy *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void calculate_enemy_distances(t_game *game)
{
    for (int i = 0; i < game->num_enemies; i++)
    {
        t_enemy *enemy = &game->enemies[i];
        enemy->dist = ((game->pg->pos_x - enemy->pos_x) * (game->pg->pos_x - enemy->pos_x) +
                       (game->pg->pos_y - enemy->pos_y) * (game->pg->pos_y - enemy->pos_y));
    }
}
