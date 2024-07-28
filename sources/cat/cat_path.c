/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:29:10 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:31:12 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_next_coords(t_game *game, int *start_x, int *start_y)
{
	int	original_x;
	int	original_y;

	original_x = *start_x;
	original_y = *start_y;
	if (original_x + 1 < game->map_cols
		&& game->map[original_y][original_x + 1] == '%')
		*start_x = original_x + 1;
	else if (original_x - 1 >= 0
		&& game->map[original_y][original_x - 1] == '%')
		*start_x = original_x - 1;
	else if (original_y + 1 < game->map_rows
		&& game->map[original_y + 1][original_x] == '%')
		*start_y = original_y + 1;
	else if (original_y - 1 >= 0
		&& game->map[original_y - 1][original_x] == '%')
		*start_y = original_y - 1;
}

void	add_path_coordinates(t_game *game)
{
	int start_x;
	int start_y;

	start_x = game->cat->map_x + 1;
	start_y = game->cat->map_y;

	while (game->cat->path_length < MAX_PATH_LENGTH)
	{
		game->map[start_y][start_x] = '0';
		get_next_coords(game, &start_x, &start_y);
		game->cat->path[game->cat->path_length].x = start_x;
		game->cat->path[game->cat->path_length].y = start_y;
		game->cat->path_length++;
	}
	game->cat->path[game->cat->path_length].x = game->door_x;
	game->cat->path[game->cat->path_length].y = game->door_y;
}
