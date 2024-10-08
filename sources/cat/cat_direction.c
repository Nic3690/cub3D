/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:31:34 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:09:11 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_cat_direction(t_cat *cat)
{
	cat->dir_x = cat->target_x - cat->pos_x;
	cat->dir_y = cat->target_y - cat->pos_y;
	cat->distance = sqrt(cat->dir_x * cat->dir_x + cat->dir_y * cat->dir_y);
	cat->dir_x = cat->dir_x / cat->distance;
	cat->dir_y = cat->dir_y / cat->distance;
}

void	update_cat_texture_state(t_game *g, t_cat *c)
{
	if (fabs(c->dir_x - g->pg->dir_x) < 0.6
		&& fabs(c->dir_y - g->pg->dir_y) < 0.6)
		update_cat_texture_near(g, c);
	else
		update_cat_texture_far(g, c);
}

void	update_cat_texture_near(t_game *g, t_cat *c)
{
	if (g->frame_count % c->wait_timer == 0 && c->death_timer == -1)
	{
		if (c->current_texture == c->escape_texture_3)
			c->current_texture = c->escape_texture_4;
		else
			c->current_texture = c->escape_texture_3;
	}
}

void	update_cat_texture_far(t_game *g, t_cat *c)
	{
	if (g->pg->dir_x - c->dir_x < 0 && g->pg->dir_y - c->dir_y > 0)
	{
		if (g->frame_count % c->wait_timer == 0 && c->death_timer == -1)
		{
			if (c->current_texture == c->escape_texture_5)
				c->current_texture = c->escape_texture_6;
			else
				c->current_texture = c->escape_texture_5;
		}
	}
	else
	{
		if (g->frame_count % c->wait_timer == 0 && c->death_timer == -1)
		{
			if (c->current_texture == c->escape_texture)
				c->current_texture = c->escape_texture_2;
			else
				c->current_texture = c->escape_texture;
		}
	}
}

void	set_death_cat_texture(t_game *game)
{
	int	frame_interval;

	frame_interval = 60;
	if (game->cat->current_texture != game->cat->dead_texture_4)
	{
		if (game->frame_count % frame_interval == 0)
			game->cat->current_texture = game->cat->dead_texture;
		else if (game->frame_count % frame_interval == frame_interval / 4)
			game->cat->current_texture = game->cat->dead_texture_2;
		else if (game->frame_count % frame_interval == frame_interval / 2)
			game->cat->current_texture = game->cat->dead_texture_3;
		else if (game->frame_count % frame_interval == 3 * frame_interval / 4)
			game->cat->current_texture = game->cat->dead_texture_4;
	}
}
