/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:22:06 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 20:05:49 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_parameters(t_game *game, t_enemy *enemy, int *visible)
{
	enemy->dir_x = game->pg->pos_x - enemy->pos_x;
	enemy->dir_y = game->pg->pos_y - enemy->pos_y;
	enemy->dist = sqrt(enemy->dir_x * enemy->dir_x
		+ enemy->dir_y * enemy->dir_y);
	enemy->dir_x /= enemy->dist;
	enemy->dir_y /= enemy->dist;
	*visible = is_visible(game, enemy);
}

void	process_death_timer(t_game *game, t_enemy *enemy, int *i)
{
	enemy->death_timer--;
	if (enemy->death_timer == 0)
	{
		game->enemies[*i] = game->enemies[game->num_enemies - 1];
		game->num_enemies--;
		(*i)--;
	}
}

void	retreat_enemy(t_game * game, t_enemy *enemy)
{
	if (enemy->retreating)
	{
		if (enemy->dir_x > 0)
			enemy->pos_x -= 0.1 * enemy->dir_x;
		else if (enemy->dir_x < 0)
			enemy->pos_x += 0.1 * fabs(enemy->dir_x);
		if (enemy->dir_y > 0)
			enemy->pos_y -= 0.1 * enemy->dir_y;
		else if (enemy->dir_y < 0)
			enemy->pos_y += 0.1 * fabs(enemy->dir_y);
		enemy->retreating = 0;
	}
	(void)game;
}

void	check_textures(t_game *game, t_enemy *enemy)
{
	if (game->frame_count % enemy->frame == 0)
	{
		if (enemy->current_texture == enemy->texture)
			enemy->current_texture = enemy->texture2;
		else
			enemy->current_texture = enemy->texture;
	}
}

int	is_visible(t_game *game, t_enemy *enemy)
{
	init_enemy_rays(game, enemy);
	perform_enemy_dda(enemy);
	while (enemy->map_x != (int)game->pg->pos_x
		|| enemy->map_y != (int)game->pg->pos_y)
	{
		if (enemy->side_dist_x < enemy->side_dist_y)
		{
			enemy->side_dist_x += enemy->delta_x;
			enemy->map_x += enemy->step_x;
		}
		else
		{
			enemy->side_dist_y += enemy->delta_y;
			enemy->map_y += enemy->step_y;
		}
		if (game->map[enemy->map_y][enemy->map_x] == '1')
			return (0);
	}
	return (1);
}
