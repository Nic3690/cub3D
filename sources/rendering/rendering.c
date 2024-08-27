/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:11 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 16:00:07 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render(t_game *g)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		calculate_ray_direction(g, x);
		identify_cell(g->pg);
		calculate_wall_distance(g, 1);
		drawing_colums(g, x);
		g->z_buffer[x] = g->pg->wall_dist;
		x++;
	}
}

int	calculate_entity_count(t_game *game)
{
	int	entity_count;

	entity_count = game->num_food + game->num_enemies + 1;
	if (!game->is_cat)
		entity_count--;
	return (entity_count);
}

void	status_and_minimap(t_game *g)
{
	if (g->win_status == 1)
		draw_win_lose(g, g->tex->you_win);
	if (g->win_status == 2)
		draw_win_lose(g, g->tex->you_die);
	if (g->win_status == 3)
		draw_win_lose(g, g->tex->you_lose);
	if (g->show_minimap)
		draw_minimap(g);
	else
		mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

void	render_entities(t_game *game, t_entity *entities, int entity_count)
{
	int	i;

	i = 0;
	while (i < entity_count)
	{
		render_entity(game, &entities[i]);
		i++;
	}
}

int	render_game(t_game *game)
{
	int			entity_count;
	t_entity	*entities;

	game->z_buffer = ft_calloc(WIDTH, sizeof(double));
	render_ceiling_and_floor(game);
	render(game);
	render_doors(game);
	entity_count = calculate_entity_count(game);
	entities = ft_calloc(entity_count, sizeof(t_entity));
	if (!entities)
		exit_game(game);
	entity_distances(game, entities, &entity_count);
	if (game->win_status == 0)
		update_enemy_textures(game);
	update_cat_textures(game);
	check_food_collision(game);
	render_entities(game, entities, entity_count);
	free(entities);
	draw_game_elements(game);
	status_and_minimap(game);
	free(game->z_buffer);
	game->frame_count++;
	return (0);
}
