/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:22:13 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:35:30 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_deltas(t_player *pg)
{
	if (pg->ray_x != 0)
		pg->delta_x = fabs(1 / pg->ray_x);
	else
		pg->delta_x = DBL_MAX;
	if (pg->ray_y != 0)
		pg->delta_y = fabs(1 / pg->ray_y);
	else
		pg->delta_y = DBL_MAX;
}

void	calculate_steps(t_player *pg)
{
	if (pg->ray_x < 0)
	{
		pg->step_x = -1;
		pg->side_x = (pg->pos_x - pg->map_x) * pg->delta_x;
	}
	else
	{
		pg->step_x = 1;
		pg->side_x = (pg->map_x + 1.0 - pg->pos_x) * pg->delta_x;
	}
	if (pg->ray_y < 0)
	{
		pg->step_y = -1;
		pg->side_y = (pg->pos_y - pg->map_y) * pg->delta_y;
	}
	else
	{
		pg->step_y = 1;
		pg->side_y = (pg->map_y + 1.0 - pg->pos_y) * pg->delta_y;
	}
}

void	calculate_wall_distance(t_game *g, int type)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		init_side(g);
		if (g->map[g->pg->map_y][g->pg->map_x] == '9' && type == 9)
			break ;
		if ((g->map[g->pg->map_y][g->pg->map_x] == '1'
			|| g->map[g->pg->map_y][g->pg->map_x] == '9') && type == 9)
			break ;
		if (g->map[g->pg->map_y][g->pg->map_x] == '1' && type == 1)
			hit = 1;
	}
	calculate_wall_side(g);
}

void	calculate_wall_side(t_game *g)
{
	if (g->pg->side == 0)
		g->pg->wall_dist = (g->pg->map_x - g->pg->pos_x
				+ (1 - g->pg->step_x) / 2) / g->pg->ray_x;
	else
		g->pg->wall_dist = (g->pg->map_y - g->pg->pos_y
				+ (1 - g->pg->step_y) / 2) / g->pg->ray_y;
}

int	calculate_line_height(t_player *pg, int side)
{
	double	wall_dist;

	if (side == 0)
		wall_dist = (pg->map_x - pg->pos_x + (1 - pg->step_x) / 2) / pg->ray_x;
	else
		wall_dist = (pg->map_y - pg->pos_y + (1 - pg->step_y) / 2) / pg->ray_y;
	return ((int)(HEIGHT / wall_dist));
}
