/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:09:19 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 16:20:54 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_textures(t_game *g)
{
	int	i;

	mlx_destroy_image(g->mlx, g->tex->food->img);
	free(g->tex->food);
	mlx_destroy_image(g->mlx, g->tex->bone->img);
	free(g->tex->bone);
	free(g->tex);
	i = 0;
	while (i < 6)
	{
		if (g->texture_paths[i])
			free(g->texture_paths[i]);
		i++;
	}
	free(g->texture_paths);
}

void	free_map(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->map_rows)
	{
		if (g->map[i])
			free(g->map[i]);
		i++;
	}
	free(g->map);
}

void	free_game_objects(t_game *g)
{
	free(g->enemies);
	free(g->food);
	if (g->cat)
		free(g->cat);
	free(g->doors);
}

void	free_graphics(t_game *g)
{
	mlx_destroy_image(g->mlx, g->img);
	mlx_destroy_image(g->mlx, g->minimap);
	mlx_clear_window(g->mlx, g->win);
	mlx_destroy_window(g->mlx, g->win);
}

int	exit_game(t_game *g)
{
	free_floor_sky_walls_doors(g);
	free_dog(g);
	free_enemies(g);
	if (g->cat)
		free_cat(g);
	free_text(g);
	free_textures(g);
	free_map(g);
	free_game_objects(g);
	free_graphics(g);
	free(g);
	exit(0);
	return (0);
}
