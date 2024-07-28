/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visibility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:39:57 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/23 13:39:58 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    init_ray(t_game *g, t_cat *cat)
{
	cat->ray_dir_x = g->pg->pos_x - cat->pos_x;
	cat->ray_dir_y = g->pg->pos_y - cat->pos_y;
	cat->distance = sqrt(cat->ray_dir_x * cat->ray_dir_x + cat->ray_dir_y * cat->ray_dir_y);
	cat->ray_dir_x /= cat->distance;
	cat->ray_dir_y /= cat->distance;
	cat->map_x = (int)cat->pos_x;
	cat->map_y = (int)cat->pos_y;
	cat->delta_x = fabs(1 / cat->ray_dir_x);
	cat->delta_y = fabs(1 / cat->ray_dir_y);
}

void	calculate_step_and_side_dist(t_cat *cat)
{
	if (cat->ray_dir_x < 0)
	{
		cat->step_x = -1;
		cat->side_dist_x = (cat->pos_x - cat->map_x) * cat->delta_x;
	}
	else
	{
		cat->step_x = 1;
		cat->side_dist_x = (cat->map_x + 1.0 - cat->pos_x) * cat->delta_x;
	}

	if (cat->ray_dir_y < 0)
	{
		cat->step_y = -1;
		cat->side_dist_y = (cat->pos_y - cat->map_y) * cat->delta_y;
	}
	else
	{
		cat->step_y = 1;
		cat->side_dist_y = (cat->map_y + 1.0 - cat->pos_y) * cat->delta_y;
	}
}

int perform_dda(t_game *game, t_cat *cat)
{
	while (cat->map_x != (int)game->pg->pos_x || cat->map_y != (int)game->pg->pos_y)
	{
		if (cat->side_dist_x < cat->side_dist_y)
		{
			cat->side_dist_x += cat->delta_x;
			cat->map_x += cat->step_x;
		}
		else
		{
			cat->side_dist_y += cat->delta_y;
			cat->map_y += cat->step_y;
		}
		if (game->map[cat->map_y][cat->map_x] == '1')
			return 0;
	}
	return 1;
}

int is_visible_cat(t_game *game)
{
	t_cat *cat;

	cat = game->cat;
	init_ray(game, cat);
	calculate_step_and_side_dist(cat);
	return (perform_dda(game, cat));
}

void    check_cat_visibility(t_game *g, t_cat *cat)
{
	int visible;

	visible = is_visible_cat(g);
	if (visible)
	{
		cat->visible = 1;
		if (cat->wait_timer <= 0)
			cat->wait_timer = 100;
	}
}
