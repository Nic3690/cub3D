/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 23:15:30 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:25:11 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	update_enemy_textures(t_game *game)
{
	int		i;
	double	attack_distance;
	double	min_dist_btw;
	t_enemy	*enemy;

	attack_distance = 0.7;
	min_dist_btw = 1.0;
	i = 0;
	while (i < game->num_enemies)
	{
		enemy = &game->enemies[i];
		if (enemy->death_timer > 0)
			process_death_timer(game, enemy, &i);
		else if (enemy->death_timer == -1)
		{
			check_textures(game, enemy);
			move_and_attack(game, enemy, attack_distance);
			retreat_enemy(game, enemy);
			distance_between_enemies(game, i, min_dist_btw);
		}
		i++;
	}
}

void	move_and_attack(t_game *game, t_enemy *enemy, double attack_distance)
{
	int	visible;

	visible = 0;
	init_parameters(game, enemy, &visible);
	if (visible && !enemy->retreating)
	{
		if (enemy->dist < attack_distance)
		{
			enemy->current_texture = enemy->attack_texture;
			if (game->frame_count % enemy->frame == 0)
			{
				game->pg->health -= enemy->damage;
				if (game->pg->health <= 0)
					game->win_status = 2;
			}
		}
		else
		{
			enemy->pos_x += enemy->dir_x * enemy->speed;
			enemy->pos_y += enemy->dir_y * enemy->speed;
			if (enemy->current_texture == enemy->attack_texture)
				enemy->current_texture = enemy->texture;
		}
	}
}

void	distance_between_enemies(t_game *game, int i, double min_dist_btw)
{
	int		j;
	double	dist_x;
	double	dist_y;
	double	dist_btw;
	double	overlap;

	j = 0;	
	while (j < game->num_enemies)
	{
		if (i != j && game->enemies[j].death_timer == -1)
		{
			dist_x = game->enemies[i].pos_x - game->enemies[j].pos_x;
			dist_y = game->enemies[i].pos_y - game->enemies[j].pos_y;
			dist_btw = sqrt(dist_x * dist_x + dist_y * dist_y);
			if (dist_btw < min_dist_btw)
			{
				overlap = min_dist_btw - dist_btw;
				game->enemies[i].pos_x += (dist_x / dist_btw) * (overlap / 2);
				game->enemies[i].pos_y += (dist_y / dist_btw) * (overlap / 2);
				game->enemies[j].pos_x -= (dist_x / dist_btw) * (overlap / 2);
				game->enemies[j].pos_y -= (dist_y / dist_btw) * (overlap / 2);
			}
		}
		j++;
	}
}

void	init_enemy_rays(t_game *game, t_enemy *enemy)
{
	enemy->ray_dir_x = game->pg->pos_x - enemy->pos_x;
	enemy->ray_dir_y = game->pg->pos_y - enemy->pos_y;
	enemy->dist = sqrt(enemy->ray_dir_x * enemy->ray_dir_x
			+ enemy->ray_dir_y * enemy->ray_dir_y);
	enemy->ray_dir_x /= enemy->dist;
	enemy->ray_dir_y /= enemy->dist;
	enemy->map_x = (int)enemy->pos_x;
	enemy->map_y = (int)enemy->pos_y;
	enemy->delta_x = fabs(1 / enemy->ray_dir_x);
	enemy->delta_y = fabs(1 / enemy->ray_dir_y);
}

void	perform_enemy_dda(t_enemy *enemy)
{
	if (enemy->ray_dir_x < 0)
	{
		enemy->step_x = -1;
		enemy->side_dist_x = (enemy->pos_x - enemy->map_x) * enemy->delta_x;
	}
	else
	{
		enemy->step_x = 1;
		enemy->side_dist_x = (enemy->map_x + 1.0 - enemy->pos_x)
			* enemy->delta_x;
	}
	if (enemy->ray_dir_y < 0)
	{
		enemy->step_y = -1;
		enemy->side_dist_y = (enemy->pos_y - enemy->map_y) * enemy->delta_y;
	}
	else
	{
		enemy->step_y = 1;
		enemy->side_dist_y = (enemy->map_y + 1.0 - enemy->pos_y)
			* enemy->delta_y;
	}
}
