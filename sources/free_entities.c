/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_entities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:12:04 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 16:17:41 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_floor_sky_walls_doors(t_game *g)
{
	free(g->pg);
	mlx_destroy_image(g->mlx, g->tex->sky->img);
	free(g->tex->sky);
	mlx_destroy_image(g->mlx, g->tex->floor->img);
	free(g->tex->floor);
	mlx_destroy_image(g->mlx, g->tex->north->img);
	free(g->tex->north);
	mlx_destroy_image(g->mlx, g->tex->south->img);
	free(g->tex->south);
	mlx_destroy_image(g->mlx, g->tex->west->img);
	free(g->tex->west);
	mlx_destroy_image(g->mlx, g->tex->east->img);
	free(g->tex->east);
	mlx_destroy_image(g->mlx, g->tex->open_door->img);
	free(g->tex->open_door);
	mlx_destroy_image(g->mlx, g->tex->closed_door->img);
	free(g->tex->closed_door);
	mlx_destroy_image(g->mlx, g->tex->door_light->img);
	free(g->tex->door_light);
}

void	free_dog(t_game *g)
{
	mlx_destroy_image(g->mlx, g->tex->paws->img);
	free(g->tex->paws);
	mlx_destroy_image(g->mlx, g->tex->blood_paws->img);
	free(g->tex->blood_paws);
	mlx_destroy_image(g->mlx, g->tex->maya->img);
	free(g->tex->maya);
	mlx_destroy_image(g->mlx, g->tex->maya_left->img);
	free(g->tex->maya_left);
	mlx_destroy_image(g->mlx, g->tex->maya_right->img);
	free(g->tex->maya_right);
	mlx_destroy_image(g->mlx, g->tex->angry_maya->img);
	free(g->tex->angry_maya);
}

void	free_enemies(t_game *g)
{
	mlx_destroy_image(g->mlx, g->tex->crow->img);
	free(g->tex->crow);
	mlx_destroy_image(g->mlx, g->tex->fly->img);
	free(g->tex->fly);
	mlx_destroy_image(g->mlx, g->tex->spider->img);
	free(g->tex->spider);
	mlx_destroy_image(g->mlx, g->tex->crow_open->img);
	free(g->tex->crow_open);
	mlx_destroy_image(g->mlx, g->tex->fly_open->img);
	free(g->tex->fly_open);
	mlx_destroy_image(g->mlx, g->tex->spider_2->img);
	free(g->tex->spider_2);
	mlx_destroy_image(g->mlx, g->tex->fly_attack->img);
	free(g->tex->fly_attack);
	mlx_destroy_image(g->mlx, g->tex->spider_attack->img);
	free(g->tex->spider_attack);
	mlx_destroy_image(g->mlx, g->tex->crow_attack->img);
	free(g->tex->crow_attack);
	mlx_destroy_image(g->mlx, g->tex->fly_dead->img);
	free(g->tex->fly_dead);
	mlx_destroy_image(g->mlx, g->tex->spider_dead->img);
	free(g->tex->spider_dead);
	mlx_destroy_image(g->mlx, g->tex->crow_dead->img);
	free(g->tex->crow_dead);
}

void	free_cat(t_game *g)
{
	mlx_destroy_image(g->mlx, g->tex->cat_dead->img);
	free(g->tex->cat_dead);
	mlx_destroy_image(g->mlx, g->tex->cat_dead_2->img);
	free(g->tex->cat_dead_2);
	mlx_destroy_image(g->mlx, g->tex->cat_dead_3->img);
	free(g->tex->cat_dead_3);
	mlx_destroy_image(g->mlx, g->tex->cat_dead_4->img);
	free(g->tex->cat_dead_4);
	mlx_destroy_image(g->mlx, g->tex->cat_escape->img);
	free(g->tex->cat_escape);
	mlx_destroy_image(g->mlx, g->tex->cat_escape_2->img);
	free(g->tex->cat_escape_2);
	mlx_destroy_image(g->mlx, g->tex->cat_escape_3->img);
	free(g->tex->cat_escape_3);
	mlx_destroy_image(g->mlx, g->tex->cat_escape_4->img);
	free(g->tex->cat_escape_4);
	mlx_destroy_image(g->mlx, g->tex->cat_face->img);
	free(g->tex->cat_face);
	mlx_destroy_image(g->mlx, g->tex->cat_escape_5->img);
	free(g->tex->cat_escape_5);
	mlx_destroy_image(g->mlx, g->tex->cat_escape_6->img);
	free(g->tex->cat_escape_6);
	free(g->cat->path);
}

void	free_text(t_game *g)
{
	mlx_destroy_image(g->mlx, g->tex->you_win->img);
	free(g->tex->you_win);
	mlx_destroy_image(g->mlx, g->tex->you_die->img);
	free(g->tex->you_die);
	mlx_destroy_image(g->mlx, g->tex->you_lose->img);
	free(g->tex->you_lose);
}
