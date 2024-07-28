/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:56:46 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:35:41 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	read_texture_paths(t_game *game, int fd)
{
	int     i;
	char    *line;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (line != NULL)
		{
			game->texture_paths[i] = ft_strdup(ft_strchr(line, 's'));
			free(line);
			i++;
		}
	}
}

void	load_textures_and_map(t_game *game, char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	game->texture_paths = malloc(sizeof(char *) * MAX_TEXTURES);
	read_texture_paths(game, fd);
	if (!load_all_textures(game))
	{
		close(fd);
		return ;
	}
	init_map(game, fd);
	close(fd);
}
