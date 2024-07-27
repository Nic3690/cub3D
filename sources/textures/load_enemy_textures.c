/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_enemy_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:50:26 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/27 12:50:46 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_crow_tex(t_game *game)
{
	game->tex->crow = malloc(sizeof(t_image));
    game->tex->crow_open = malloc(sizeof(t_image));
    game->tex->crow_attack = malloc(sizeof(t_image));
    game->tex->crow_dead = malloc(sizeof(t_image));
	if (!game->tex->crow || !game->tex->crow_open
		|| !game->tex->crow_attack || !game->tex->crow_dead)
		exit_game(game);
	load_texture(game, game->tex->crow, "sprites/crow_open.xpm");
    load_texture(game, game->tex->crow_open, "sprites/crow_closed.xpm");
    load_texture(game, game->tex->crow_attack, "sprites/crow_attack.xpm");
    load_texture(game, game->tex->crow_dead, "sprites/poltigliadicornacchia.xpm");
}

void	load_fly_tex(t_game *game)
{
    game->tex->fly = malloc(sizeof(t_image));
    game->tex->fly_open = malloc(sizeof(t_image));
	game->tex->fly_attack = malloc(sizeof(t_image));
    game->tex->fly_dead = malloc(sizeof(t_image));
	if (!game->tex->fly || !game->tex->fly_open
		|| !game->tex->fly_attack || !game->tex->fly_dead)
		exit_game(game);
    load_texture(game, game->tex->fly, "sprites/fly_open.xpm");
    load_texture(game, game->tex->fly_open, "sprites/fly_closed.xpm");
	load_texture(game, game->tex->fly_attack, "sprites/fly_attack.xpm");
    load_texture(game, game->tex->fly_dead, "sprites/poltigliadimosca.xpm");
}

void	load_spider_tex(t_game *game)
{
    game->tex->spider = malloc(sizeof(t_image));
    game->tex->spider_2 = malloc(sizeof(t_image));
    game->tex->spider_attack = malloc(sizeof(t_image));
    game->tex->spider_dead = malloc(sizeof(t_image));
	if (!game->tex->spider || !game->tex->spider_2
		|| !game->tex->spider_attack || !game->tex->spider_dead)
		exit_game(game);
    load_texture(game, game->tex->spider, "sprites/spider_open.xpm");
    load_texture(game, game->tex->spider_2, "sprites/spider_closed.xpm");
    load_texture(game, game->tex->spider_attack, "sprites/spider_attack.xpm");
    load_texture(game, game->tex->spider_dead, "sprites/poltigliadiragno.xpm");
}

void	load_enemies_tex(t_game *game)
{
	load_crow_tex(game);
	load_fly_tex(game);
	load_spider_tex(game);
}
