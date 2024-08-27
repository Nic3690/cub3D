/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:37:36 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:27:03 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	start_attack(t_game *game)
{
	if (game->pg->attack_cooldown == 0)
	{
		game->pg->attack = 1;
		game->pg->attack_time = 3;
		game->pg->attack_cooldown = 3;
	}
}

void	update_attack_status(t_game *game)
{
	if (game->pg->attack)
	{
		if (game->pg->attack_time > 0)
			game->pg->attack_time--;
		else
		{
			game->pg->attack = 0;
			game->pg->attack_cooldown = 3;
		}
	}
	else
	{
		if (game->pg->attack_cooldown > 0)
			game->pg->attack_cooldown--;
	}
}

void	attack_enemy(t_game *g, t_enemy *e, int a_damage, double a_distance)
{
	double	dir_x;
	double	dir_y;
	double	distance;

	dir_x = e->pos_x - g->pg->pos_x;
	dir_y = e->pos_y - g->pg->pos_y;
	distance = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (distance < a_distance && g->pg->attack_time >= 3)
	{
		e->enemy_health -= a_damage;
		e->retreating = 1;
		if (e->enemy_health <= 0 && e->death_timer == -1)
		{
			e->current_texture = e->dead_texture;
			e->death_timer = 300;
		}
	}
}

void	attack_cat(t_game *game, int a_damage, double a_distance)
{
	double	dir_x;
	double	dir_y;
	double	distance;

	dir_x = game->cat->pos_x - game->pg->pos_x;
	dir_y = game->cat->pos_y - game->pg->pos_y;
	distance = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (distance < a_distance && game->pg->attack_time >= 3)
	{
		game->cat->health -= a_damage;
		if (game->cat->health <= 0 && game->cat->death_timer == -1)
		{
			game->cat->current_texture = game->cat->dead_texture;
			game->cat->death_timer = 300;
			game->win_status = 1;
		}
	}
}

void	player_attack(t_game *game)
{
	int		a_damage;
	double	a_distance;
	int		i;

	a_damage = 10;
	a_distance = 0.7;
	i = 0;
	while (i < game->num_enemies && game->win_status == 0)
	{
		attack_enemy(game, &game->enemies[i], a_damage, a_distance);
		i++;
	}
	attack_cat(game, a_damage, a_distance);
}
