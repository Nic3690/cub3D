/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:52:59 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:25:56 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_doors(t_game *game, int x, int y, int *index)
{
	if (game->map[y][x] == DOOR)
	{
		game->doors[*index].pos_x = x;
		game->doors[*index].pos_y = y;
		game->doors[*index].is_open = 0;
		game->doors[*index].open_tex = game->tex->open_door;
		game->doors[*index].closed_tex = game->tex->closed_door;
		game->doors[*index].curr_tex = game->tex->closed_door;
		(*index)++;
	}
}

void	check_food(t_game *game, int x, int y, int *index)
{
	if (game->map[y][x] == FOOD)
	{
		game->food[*index].texture = game->tex->food;
		game->food[*index].type = 0;
	}
	else if (game->map[y][x] == BONE)
	{
		game->food[*index].texture = game->tex->bone;
		game->food[*index].type = 1;
	}
	if (game->map[y][x] == FOOD || game->map[y][x] == BONE)
	{
		game->food[*index].pos_x = x + 0.5;
		game->food[*index].pos_y = y + 0.5;
		(*index)++;
	}
}

void	check_and_set_enemy(t_game *game, int x, int y, int *index)
{
	if (game->map[y][x] == FLY)
		set_fly_properties(game, *index);
	else if (game->map[y][x] == SPIDER)
		set_spider_properties(game, *index);
	else if (game->map[y][x] == CROW)
		set_crow_properties(game, *index);
	if (game->map[y][x] == FLY || game->map[y][x] == SPIDER
		|| game->map[y][x] == CROW)
	{
		set_enemy_position(game, x, y, *index);
		(*index)++;
		game->map[y][x] = '0';
	}
}

