/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:57:20 by nfurlani          #+#    #+#             */
/*   Updated: 2024/08/27 15:58:39 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_tex_color(t_image *image, int tex_x, int tex_y)
{
	int	*texture;

	if (tex_x < 0 || tex_x >= image->w || tex_y < 0 || tex_y >= image->h)
		return (0);
	texture = (int *)image->addr;
	return (texture[tex_y * image->w + tex_x]);
}

void	drawing(t_game *g, t_image *image, double tex_pos, int x)
{
	int	y;
	int	color;

	y = g->draw->draw_start;
	while (y < g->draw->draw_end)
	{
		g->draw->tex_y = (int)tex_pos & (g->tex->tex_h - 1);
		tex_pos += g->draw->step;
		color = get_tex_color(image, g->draw->tex_x, g->draw->tex_y);
		if (color != (0xFF << 24))
			pixel_put(g, x, y, color);
		y++;
	}
}

void	drawing_colums(t_game *g, int x)
{
	t_draw	*draw;

	draw = ft_calloc(1, sizeof(t_draw));
	if (!draw)
		return ;
	draw->line = (int)(HEIGHT / g->pg->wall_dist);
	draw->draw_start = -draw->line / 2 + HEIGHT / 2;
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = draw->line / 2 + HEIGHT / 2;
	if (draw->draw_end >= HEIGHT)
		draw->draw_end = HEIGHT - 1;
	if (g->pg->side == 0)
		draw->wall_x = g->pg->pos_y + g->pg->wall_dist * g->pg->ray_y;
	else
		draw->wall_x = g->pg->pos_x + g->pg->wall_dist * g->pg->ray_x;
	draw->wall_x -= floor(draw->wall_x);
	g->draw = draw;
	render_wall_column(g, x, g->pg->side);
	free(draw);
}

void	draw_win_lose(t_game *game, t_image *texture)
{
	int	x;
	int	y;
	int	screen_x_start;
	int	screen_y_start;
	int	color;

	y = 0;
	color = 0;
	screen_x_start = (WIDTH - (texture->w * 15)) / 2;
	screen_y_start = (HEIGHT - (texture->h * 15)) / 2;
	while (y < texture->h * 15)
	{
		x = 0;
		while (x < texture->w * 15)
		{
			color = get_tex_color(texture, x / 15, y / 15);
			if (color != (0xFF << 24))
				pixel_put(game, screen_x_start + x, screen_y_start + y, color);
			x++;
		}
		y++;
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
