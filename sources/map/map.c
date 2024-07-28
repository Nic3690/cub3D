/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:34:55 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:36:26 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_direction_ns(t_game *game, char dir)
{
	if (dir == NORTH)
	{
		game->pg->dir_x = 0;
		game->pg->dir_y = -1;
		game->pg->plane_x = 0.66;
		game->pg->plane_y = 0;
	}
	else if (dir == SOUTH)
	{
		game->pg->dir_x = 0;
		game->pg->dir_y = 1;
		game->pg->plane_x = -0.66;
		game->pg->plane_y = 0;
	}
}

void	set_player_direction_we(t_game *game, char dir)
{
	if (dir == EAST)
	{
		game->pg->dir_x = 1;
		game->pg->dir_y = 0;
		game->pg->plane_x = 0;
		game->pg->plane_y = 0.66;
	}
	else if (dir == WEST)
	{
		game->pg->dir_x = -1;
		game->pg->dir_y = 0;
		game->pg->plane_x = 0;
		game->pg->plane_y = -0.66;
	}
}

void	get_rows_and_cols(t_game *game, int fd, char **buffer)
{
	int i;
	int len;

	i = 0;
	get_next_line(fd);
	buffer[i] = get_next_line(fd);
	while (buffer[i] != NULL)
	{
		len = ft_strlen(buffer[i]);
		if (len > game->map_cols)
			game->map_cols = len;
		i++;
		buffer[i] = get_next_line(fd);
	}
	game->map_rows = i;
}

void	copy_map(t_game *game, char **buffer)
{
	int i;

	i = 0;
	game->map = malloc(sizeof(char *) * game->map_rows);
	while (i < game->map_rows)
	{
		game->map[i] = malloc(sizeof(char)
			* (game->map_cols + 1));
		ft_bzero(game->map[i], game->map_cols, ' ');
		ft_strcpy(game->map[i], buffer[i]);
		free(buffer[i]);
		i++;
	}
	if (!count_pg(game))
	{
		printf("Error\nInvalid number of players\n");
		exit_game(game);
	}
}
