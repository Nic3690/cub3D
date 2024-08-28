/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:29:14 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/28 18:02:50 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->addr + (y * game->line + x * (game->bits / 8));
	*(unsigned int *)dst = color;
}

void	init_parameters_game(t_game *g)
{
	g->frame_count = 0;
	g->pg->health = 100;
	g->face_state = 0;
	g->face_timer = 300;
	g->num_doors = 0;
	g->num_enemies = 0;
	g->num_food = 0;
	g->show_minimap = 0;
	g->win_status = 0;
}

void	init_game(t_game *g)
{
	g->map_width = WIDTH;
	g->map_height = HEIGHT;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, g->map_width, g->map_height, "Cub3D");
	g->img = mlx_new_image(g->mlx, g->map_width, g->map_height);
	g->addr = mlx_get_data_addr(g->img, &g->bits, &g->line, &g->endian);
	g->minimap = mlx_new_image(g->mlx, g->map_width, g->map_height);
	g->miniaddr = mlx_get_data_addr
		(g->minimap, &g->minibits, &g->miniline, &g->miniendian);
	g->pg = ft_calloc(1, sizeof(t_player));
	if (!g->pg)
		exit_game(g);
	g->tex = ft_calloc(1, sizeof(t_texture));
	if (!g->tex)
		exit_game(g);
	init_parameters_game(g);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (0);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		exit_game(game);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		printf ("Error\nInvalid file extension\n");
		free(game);
		exit_game(game);
	}
	init_game(game);
	load_textures_and_map(game, argv[1]);
	check_valid_map(game);
	game->pg->move_speed = 0.06;
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	render_ceiling_and_floor(game);
	mlx_loop_hook(game->mlx, &render_game, game);
	mlx_loop(game->mlx);
	return (0);
}
