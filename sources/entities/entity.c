/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:34:39 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 17:35:51 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sort_entities_by_distance(t_entity *entities, int *entity_count)
{
	int			i;
	int			j;
	t_entity	temp;

	i = 0;
	j = 0;
	temp = entities[i];
	while (i < *entity_count - 1)
	{
		j = i + 1;
		while (j < *entity_count)
		{
			if (entities[i].dist < entities[j].dist)
			{
				temp = entities[i];
				entities[i] = entities[j];
				entities[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	entity_distances(t_game *game, t_entity *entities, int *entity_count)
{
	*entity_count = 0;
	add_food(game, entities, entity_count);
	add_enemy(game, entities, entity_count);
	add_cat(game, entities, entity_count);
	sort_entities_by_distance(entities, entity_count);
}
