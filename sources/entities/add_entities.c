/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:35:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/30 21:02:01 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_food(t_game *game, t_entity *entities, int *entity_count)
{
	int i;

	i = 0;
	while (i < game->num_food)
	{
		if (game->food[i].active)
		{
			entities[*entity_count].pos_x = game->food[i].pos_x;
			entities[*entity_count].pos_y = game->food[i].pos_y;
			entities[*entity_count].tex = game->food[i].texture;
			entities[*entity_count].dist =
				((game->pg->pos_x - game->food[i].pos_x)
				* (game->pg->pos_x - game->food[i].pos_x)
				+ (game->pg->pos_y - game->food[i].pos_y)
				* (game->pg->pos_y - game->food[i].pos_y));
			(*entity_count)++;
		}
		i++;
	}
}

void	add_enemy(t_game *game, t_entity *entities, int *entity_count)
{
	int i;

	i = 0;
	while (i < game->num_enemies)
	{
		entities[*entity_count].pos_x = game->enemies[i].pos_x;
		entities[*entity_count].pos_y = game->enemies[i].pos_y;
		entities[*entity_count].tex = game->enemies[i].current_texture;
		entities[*entity_count].dist =
			((game->pg->pos_x - game->enemies[i].pos_x)
			* (game->pg->pos_x - game->enemies[i].pos_x)
			+ (game->pg->pos_y - game->enemies[i].pos_y)
			* (game->pg->pos_y - game->enemies[i].pos_y));
		(*entity_count)++;
		i++;
	}
}

void	add_cat(t_game *game, t_entity *entities, int *entity_count)
{
	if (game->is_cat)
	{
		entities[*entity_count].pos_x = game->cat->pos_x;
		entities[*entity_count].pos_y = game->cat->pos_y;
		entities[*entity_count].tex = game->cat->current_texture;
		entities[*entity_count].dist =
			((game->pg->pos_x - game->cat->pos_x)
			* (game->pg->pos_x - game->cat->pos_x)
			+ (game->pg->pos_y - game->cat->pos_y)
			* (game->pg->pos_y - game->cat->pos_y));
		(*entity_count)++;
	}
}
