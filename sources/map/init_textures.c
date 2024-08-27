/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:30:43 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 16:09:31 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	read_texture_paths(t_game *game, int fd)
{
	int		i;
	char	*line;
	char	**path;

	i = -1;
	path = ft_calloc(6, sizeof(char *));
	while (++i < 6)
	{
		line = get_next_line(fd);
		if (!line)
			continue ;
		path[i] = line;
	}
	sort_paths(path);
	if (!check_valid_path(path))
		exit_game(game);
	i = -1;
	while (++i < 6)
	{
		game->texture_paths[i] = ft_strdup(ft_strchr(path[i], 's'));
		free(path[i]);
	}
	free(path);
}

void	load_textures_and_map(t_game *game, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_game(game);
	game->texture_paths = ft_calloc(MAX_TEXTURES, sizeof(char *));
	read_texture_paths(game, fd);
	if (!load_all_textures(game))
	{
		close(fd);
		return ;
	}
	init_map(game, fd);
	close(fd);
}

void	validate_and_sort_path(char **path, char **sorted, int index)
{
	if (ft_strncmp(path[index], "NO", 2) == 0 && !sorted[0])
		sorted[0] = path[index];
	else if (ft_strncmp(path[index], "SO", 2) == 0 && !sorted[1])
		sorted[1] = path[index];
	else if (ft_strncmp(path[index], "WE", 2) == 0 && !sorted[2])
		sorted[2] = path[index];
	else if (ft_strncmp(path[index], "EA", 2) == 0 && !sorted[3])
		sorted[3] = path[index];
	else if (ft_strncmp(path[index], "F", 1) == 0 && !sorted[4])
		sorted[4] = path[index];
	else if (ft_strncmp(path[index], "C", 1) == 0 && !sorted[5])
		sorted[5] = path[index];
	else
	{
		printf ("Error\nInvalid Key\n");
		exit(1);
	}
}

void	sort_paths(char **path)
{
	int		i;
	char	*sorted[6];

	i = 0;
	while (i < 6)
		sorted[i++] = NULL;
	i = 0;
	while (i < 6)
	{
		validate_and_sort_path(path, sorted, i);
		i++;
	}
	i = 0;
	while (i < 6)
	{
		path[i] = sorted[i];
		i++;
	}
}

int	check_valid_path(char **path)
{
	int	flag;

	flag = 1;
	if (ft_strncmp(path[0], "NO", 2) != 0)
		flag = 0;
	else if (ft_strncmp(path[1], "SO", 2) != 0)
		flag = 0;
	else if (ft_strncmp(path[2], "WE", 2) != 0)
		flag = 0;
	else if (ft_strncmp(path[3], "EA", 2) != 0)
		flag = 0;
	else if (ft_strncmp(path[4], "F", 1) != 0)
		flag = 0;
	else if (ft_strncmp(path[5], "C", 1) != 0)
		flag = 0;
	return (flag);
}
