/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:52:32 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:37:34 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_enemy_at(t_game *game, double x, double y)
{
	int i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].death_timer == -1
			&& fabs(x - game->enemies[i].pos_x) < 0.5
			&& fabs(y - game->enemies[i].pos_y) < 0.5)
			return (1);
		i++;
	}
	return (0);
}

int	is_food(t_game *game, double x, double y)
{
	int i;

	i = 0;
	while (i < game->num_food)
	{
		if (fabs(x - game->food[i].pos_x) < 0.5
			&& fabs(y - game->food[i].pos_y) < 0.5)
			return (1);
		i++;
	}
	return (0);
}

int	is_door_open(t_game *game, double x, double y)
{
	int i;

	i = 0;
	while (i < game->num_doors)
	{
		if (fabs(x - game->doors[i].pos_x) < 1
			&& fabs(y - game->doors[i].pos_y) < 1)
		{
			if (game->doors[i].is_open == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_cat_at(t_game *game, double x, double y)
{
	if (fabs(x - game->cat->pos_x) < 0.5
		&& fabs(y - game->cat->pos_y) < 0.5)
		return (1);
	return (0);
}
