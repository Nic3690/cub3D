/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:09:19 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/29 19:47:15 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_floor_sky_walls_doors(t_game *g)
{
	if (g->pg)
		free(g->pg);
	if (g->tex->sky)
		free(g->tex->sky);
	if (g->tex->floor)
		free(g->tex->floor);
	if (g->tex->north)
		free(g->tex->north);
	if (g->tex->south)
		free(g->tex->south);
	if (g->tex->west)
		free(g->tex->west);
	if (g->tex->east)
		free(g->tex->east);
	if (g->tex->open_door)
		free(g->tex->open_door);
	if (g->tex->closed_door)
		free(g->tex->closed_door);
}

void	free_dog(t_game *g)
{
	if (g->tex->paws)
		free(g->tex->paws);
	if (g->tex->blood_paws)
		free(g->tex->blood_paws);
	if (g->tex->maya)
		free(g->tex->maya);
	if (g->tex->maya_left)
		free(g->tex->maya_left);
	if (g->tex->maya_right)
		free(g->tex->maya_right);
	if (g->tex->angry_maya)
		free(g->tex->angry_maya);
}

void	free_enemies(t_game *g)
{
	if (g->tex->crow)
		free(g->tex->crow);
	if (g->tex->fly)
		free(g->tex->fly);
	if (g->tex->spider)
		free(g->tex->spider);
	if (g->tex->crow_open)
		free(g->tex->crow_open);
	if (g->tex->fly_open)
		free(g->tex->fly_open);
	if (g->tex->spider_2)
		free(g->tex->spider_2);
	if (g->tex->fly_attack)
		free(g->tex->fly_attack);
	if (g->tex->spider_attack)
		free(g->tex->spider_attack);
	if (g->tex->crow_attack)
		free(g->tex->crow_attack);
	if (g->tex->fly_dead)
		free(g->tex->fly_dead);
	if (g->tex->spider_dead)
		free(g->tex->spider_dead);
	if (g->tex->crow_dead)
		free(g->tex->crow_dead);
}

void	free_cat(t_game *g)
{
	if (g->cat)
	{
		if (g->tex->cat_dead)
			free(g->tex->cat_dead);
		if (g->tex->cat_escape)
			free(g->tex->cat_escape);
		if (g->tex->cat_escape_2)
			free(g->tex->cat_escape_2);
		if (g->tex->cat_escape_3)
			free(g->tex->cat_escape_3);
		if (g->tex->cat_escape_4)
			free(g->tex->cat_escape_4);
		if (g->tex->cat_face)
			free(g->tex->cat_face);
		if (g->tex->cat_escape_5)
			free(g->tex->cat_escape_5);
		if (g->tex->cat_escape_6)
			free(g->tex->cat_escape_6);
	}
	if (g->tex->you_win)
		free(g->tex->you_win);
	if (g->tex->you_die)
		free(g->tex->you_die);
	if (g->tex->you_lose)
		free(g->tex->you_lose);
}

void    exit_game(t_game *g)
{
	free_floor_sky_walls_doors(g);
	free_dog(g);
	free_enemies(g);
	free_cat(g);
	if (g->tex->food)
		free(g->tex->food);
	if (g->tex->bone)
		free(g->tex->bone);
	if (g->tex)
		free(g->tex);
	if (g->map)
		free(g->map);
	if (g->enemies)
		free(g->enemies);
	if (g->food)
		free(g->food);
	if (g->cat)
		free(g->cat);
	if (g->texture_paths)
		free(g->texture_paths);
	mlx_clear_window(g->mlx, g->win);
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
}
