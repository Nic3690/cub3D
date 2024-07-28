/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_enemy_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:50:26 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 21:45:52 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    check_malloc(t_game *g)
{
	if (!g->tex->cat_dead || !g->tex->cat_escape
		|| !g->tex->cat_escape_2 || !g->tex->cat_escape_3
		|| !g->tex->cat_escape_4 || !g->tex->cat_face
		|| !g->tex->cat_escape_5 || !g->tex->cat_escape_6
		|| !g->tex->cat_dead_2 || !g->tex->cat_dead_3 || !g->tex->cat_dead_4)
		exit_game(g);
}

void	load_cat_tex(t_game *g)
{
	g->tex->cat_dead = malloc(sizeof(t_image));
	g->tex->cat_dead_2 = malloc(sizeof(t_image));
	g->tex->cat_dead_3 = malloc(sizeof(t_image));
	g->tex->cat_dead_4 = malloc(sizeof(t_image));
	g->tex->cat_escape = malloc(sizeof(t_image));
	g->tex->cat_escape_2 = malloc(sizeof(t_image));
	g->tex->cat_escape_3 = malloc(sizeof(t_image));
	g->tex->cat_escape_4 = malloc(sizeof(t_image));
	g->tex->cat_escape_5 = malloc(sizeof(t_image));
	g->tex->cat_escape_6 = malloc(sizeof(t_image));
	g->tex->cat_face = malloc(sizeof(t_image));
	check_malloc(g);
	load_texture(g, g->tex->cat_dead, "sprites/mismisvola.xpm");
	load_texture(g, g->tex->cat_dead_2, "sprites/mismisvolavola.xpm");
	load_texture(g, g->tex->cat_dead_3, "sprites/mismisvolavolavola.xpm");
	load_texture(g, g->tex->cat_dead_4, "sprites/mismisnoncepiu.xpm");
	load_texture(g, g->tex->cat_escape, "sprites/misescaping_1.xpm");
	load_texture(g, g->tex->cat_escape_2, "sprites/misescaping_2.xpm");
	load_texture(g, g->tex->cat_escape_3, "sprites/mismisescapediculo.xpm");
	load_texture(g, g->tex->cat_escape_4, "sprites/mismisescapediculo_2.xpm");
	load_texture(g, g->tex->cat_escape_5, "sprites/misescaping_3.xpm");
	load_texture(g, g->tex->cat_escape_6, "sprites/misescaping_4.xpm");
	load_texture(g, g->tex->cat_face, "sprites/mismis_face.xpm");
}

void	load_crow_tex(t_game *g)
{
	g->tex->crow = malloc(sizeof(t_image));
	g->tex->crow_open = malloc(sizeof(t_image));
	g->tex->crow_attack = malloc(sizeof(t_image));
	g->tex->crow_dead = malloc(sizeof(t_image));
	if (!g->tex->crow || !g->tex->crow_open
		|| !g->tex->crow_attack || !g->tex->crow_dead)
		exit_game(g);
	load_texture(g, g->tex->crow, "sprites/crow_open.xpm");
	load_texture(g, g->tex->crow_open, "sprites/crow_closed.xpm");
	load_texture(g, g->tex->crow_attack, "sprites/crow_attack.xpm");
	load_texture(g, g->tex->crow_dead, "sprites/poltigliadicornacchia.xpm");
}

void	load_fly_tex(t_game *g)
{
	g->tex->fly = malloc(sizeof(t_image));
	g->tex->fly_open = malloc(sizeof(t_image));
	g->tex->fly_attack = malloc(sizeof(t_image));
	g->tex->fly_dead = malloc(sizeof(t_image));
	if (!g->tex->fly || !g->tex->fly_open
		|| !g->tex->fly_attack || !g->tex->fly_dead)
		exit_game(g);
	load_texture(g, g->tex->fly, "sprites/fly_open.xpm");
	load_texture(g, g->tex->fly_open, "sprites/fly_closed.xpm");
	load_texture(g, g->tex->fly_attack, "sprites/fly_attack.xpm");
	load_texture(g, g->tex->fly_dead, "sprites/poltigliadimosca.xpm");
}

void	load_spider_tex(t_game *g)
{
	g->tex->spider = malloc(sizeof(t_image));
	g->tex->spider_2 = malloc(sizeof(t_image));
	g->tex->spider_attack = malloc(sizeof(t_image));
	g->tex->spider_dead = malloc(sizeof(t_image));
	if (!g->tex->spider || !g->tex->spider_2
		|| !g->tex->spider_attack || !g->tex->spider_dead)
		exit_game(g);
	load_texture(g, g->tex->spider, "sprites/spider_open.xpm");
	load_texture(g, g->tex->spider_2, "sprites/spider_closed.xpm");
	load_texture(g, g->tex->spider_attack, "sprites/spider_attack.xpm");
	load_texture(g, g->tex->spider_dead, "sprites/poltigliadiragno.xpm");
}
