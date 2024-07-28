/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:28:11 by nfurlani          #+#    #+#             */
/*   Updated: 2024/07/28 21:47:03 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_wall_sky_doors_tex(t_game *game)
{
	game->tex->sky = malloc(sizeof(t_image));
	game->tex->floor = malloc(sizeof(t_image));
	game->tex->north = malloc(sizeof(t_image));
	game->tex->south = malloc(sizeof(t_image));
	game->tex->west = malloc(sizeof(t_image));
	game->tex->east = malloc(sizeof(t_image));
	game->tex->door_light = malloc(sizeof(t_image));
	game->tex->open_door = malloc(sizeof(t_image));
	game->tex->closed_door = malloc(sizeof(t_image));
	if (!game->tex->sky || !game->tex->floor || !game->tex->north
		|| !game->tex->south || !game->tex->west || !game->tex->east)
		exit_game(game);
	load_texture(game, game->tex->east, game->texture_paths[0]);
	load_texture(game, game->tex->south, game->texture_paths[1]);
	load_texture(game, game->tex->north, game->texture_paths[2]);
	load_texture(game, game->tex->west, game->texture_paths[3]);
	load_texture(game, game->tex->floor, game->texture_paths[4]);
	load_texture(game, game->tex->sky, game->texture_paths[5]);
	load_texture(game, game->tex->door_light, "sprites/cat_door_light.xpm");
	load_texture(game, game->tex->closed_door, "sprites/gate_light.xpm");
	load_texture(game, game->tex->open_door, "sprites/gate_light_open.xpm");
}

void	load_dog_tex(t_game *game)
{
	game->tex->paws = malloc(sizeof(t_image));
	game->tex->blood_paws = malloc(sizeof(t_image));
	game->tex->maya = malloc(sizeof(t_image));
	game->tex->maya_left = malloc(sizeof(t_image));
	game->tex->maya_right = malloc(sizeof(t_image));
	game->tex->angry_maya = malloc(sizeof(t_image));
	if (!game->tex->paws || !game->tex->blood_paws || !game->tex->maya
		|| !game->tex->maya_left || !game->tex->maya_right
		|| !game->tex->angry_maya)
		exit_game(game);
	load_texture(game, game->tex->paws, "sprites/paws.xpm");
	load_texture(game, game->tex->blood_paws, "sprites/nontranquipaws.xpm");
	load_texture(game, game->tex->maya, "sprites/maya_1.xpm");
	load_texture(game, game->tex->maya_left, "sprites/maya_2.xpm");
	load_texture(game, game->tex->maya_right, "sprites/maya_3.xpm");
	load_texture(game, game->tex->angry_maya, "sprites/angry_maya.xpm");
}

int	load_all_textures(t_game *game)
{
	load_wall_sky_doors_tex(game);
	load_enemies_tex(game);
	load_cat_tex(game);
	load_dog_tex(game);
	game->tex->food = malloc(sizeof(t_image));
	game->tex->bone = malloc(sizeof(t_image));
	game->tex->you_win = malloc(sizeof(t_image));
	game->tex->you_die = malloc(sizeof(t_image));
	game->tex->you_lose = malloc(sizeof(t_image));
	if (!game->tex->food || !game->tex->bone || !game->tex->you_win
		|| !game->tex->you_die || !game->tex->you_lose)
		exit_game(game);
	load_texture(game, game->tex->food, "sprites/food.xpm");
	load_texture(game, game->tex->bone, "sprites/bone.xpm");
	load_texture(game, game->tex->you_win, "sprites/you_win.xpm");
	load_texture(game, game->tex->you_die, "sprites/you_died.xpm");
	load_texture(game, game->tex->you_lose, "sprites/you_lose.xpm");
	return (1);
}

int	load_texture(t_game *game, t_image *image, const char *path)
{
	int width;
	int height;

	width = 64;
	height = 64;
	image->img = mlx_xpm_file_to_image(game->mlx, (char *)path, &width, &height);
	if (!image->img)
		return (0);
	image->addr = mlx_get_data_addr(image->img, &image->bits,
		&image->line, &image->endian);
	if (!image->addr)
	{
		mlx_destroy_image(game->mlx, game->image->img);
		return (0);
	}
	image->w = width;
	image->h = height;
	return (1);
}

void	load_enemies_tex(t_game *game)
{
	load_crow_tex(game);
	load_fly_tex(game);
	load_spider_tex(game);
}
