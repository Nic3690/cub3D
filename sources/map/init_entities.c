/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:54:40 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/30 20:53:20 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	increment_entity_counts(t_game *game, int x, int y)
{
	if (game->map[y][x] == FLY || game->map[y][x] == SPIDER
		|| game->map[y][x] == CROW)
		game->num_enemies++;
	else if (game->map[y][x] == FOOD || game->map[y][x] == BONE)
		game->num_food++;
	else if (game->map[y][x] == DOOR)
		game->num_doors++;
}

void	scan_map_for_entities(t_game *game)
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

void	allocate_entities(t_game *game)
{
	game->enemies = ft_calloc(game->num_enemies, sizeof(t_enemy));
	if (game->enemies == NULL)
		exit_game(game);
	game->food = ft_calloc(game->num_food, sizeof(t_food));
	if (game->food == NULL)
		exit_game(game);
	game->doors = ft_calloc(game->num_doors, sizeof(t_door));
	if (game->doors == NULL)
		exit_game(game);
	game->cat = ft_calloc(1, sizeof(t_cat));
	if (game->cat == NULL)
		exit_game(game);
}
