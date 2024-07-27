/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:51:11 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 11:58:45 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    render(t_game *g)
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

int render_game(t_game *game)
{
    int			entity_count;
    t_entity	*entities;
    
    game->z_buffer = malloc(sizeof(double) * WIDTH);
    render_ceiling_and_floor(game);
    render(game);
    render_doors(game);
    entity_count = calculate_entity_count(game);
    entities = malloc(sizeof(t_entity) * entity_count);
    if (!entities)
        exit_game(game);
    entity_distances(game, entities, &entity_count);
    update_cat_textures(game);
    update_enemy_textures(game);
    check_food_collision(game);
    render_entities(game, entities, entity_count);
    free(entities);
    draw_game_elements(game);
    if (game->show_minimap)
        draw_minimap(game);
    else
        mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    free(game->z_buffer);
    game->frame_count++;
    return (0);
}

int	calculate_entity_count(t_game *game)
{
    int	entity_count;

	entity_count = game->num_food + game->num_enemies + 1;
    if (!game->is_cat)
        entity_count--;
    return (entity_count);
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

void	draw_game_elements(t_game *game)
{
    draw_paws_attack(game);
    draw_health_bar(game);
    draw_health_bar_cat(game);
    update_face_state(game);
    draw_face(game);
    draw_face_cat(game);
}
